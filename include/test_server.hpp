#ifndef TEST_SERVER_HPP
#define TEST_SERVER_HPP

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <exception>
#include <iostream>
#include <vector>

#include <pthread.h>

// socket을 위한 헤더파일
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>

// select을 위한 헤더파일
#include <sys/select.h>

// poll을 위한 헤더파일
#include <poll.h>

// kqueue를 위한 헤더파일
#include <sys/event.h>

#define BUFSIZE 1024

class test_server
{
    private:
    int socket_fd;
    int my_port;
    struct sockaddr_in server_addr;

    void bind_server()
    {
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(my_port);
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            throw std::exception();
        }
    }

    int listen_server()
    {
        return (listen(socket_fd, 5));
    }

    int accept_server()
    {
        struct sockaddr_in client_addr;
        int clnt_addr_size;
        clnt_addr_size = sizeof(client_addr);
        return (accept(socket_fd, (struct sockaddr*)&client_addr, (socklen_t *)&clnt_addr_size));
    }

    /**
     * 멀티 프로세스 기반
     * 각 클라이언트 소켓 fd 마다 프로세스를 fork()
     *  부모 프로세스 : 리스닝 소켓 (server)
     *  자식 프로세스 : 클라언트 소켓 (clinet)
     */
    void multi_process_run()
    {
        pid_t pid;
        int clnt_sock;
        int str_len;
        char message[BUFSIZE];

        while (1)
        {
            // client acppet
            clnt_sock = accept_server();
            if (clnt_sock == -1)
                continue;
            std::cout << "[client " << clnt_sock << "] Connected!" << std::endl;

            // 프로세스 fork
            pid = fork();
            if (pid == -1)
            {
                close(clnt_sock);
                std::cout << "[client " << clnt_sock << "] Disconnected" << std::endl;
                continue;
            }
            else if (pid == 0)
            {
                // 자식 프로세스에서는 서버 소켓 닫기
                close(socket_fd);

                // data read
                while( (str_len = read(clnt_sock, message, BUFSIZE)) != 0)
                {
                    write(clnt_sock, message, str_len);
                    std::string str(message, str_len);
                    std::cout << "[client " << clnt_sock << "] : " << str << std::endl;
                }

                // disconnect client
                close(clnt_sock);
                std::cout << "[client " << clnt_sock << "] Disconnected" << std::endl;
                exit(0);
            }
        }
        close(socket_fd);
    }

    static void *client_thread_handling(void *sock)
    {
        int clnt_sock = *((int *)sock);
        int str_len;
        char message[BUFSIZE];

        // data read
        while( (str_len = read(clnt_sock, message, BUFSIZE)) != 0)
        {
            write(clnt_sock, message, str_len);
            std::string str(message, str_len);
            std::cout << "[client " << clnt_sock << "] : " << str << std::endl;
        }

        // disconnect client
        std::cout << "[client " << clnt_sock << "] Disconnected" << std::endl;
        close(clnt_sock);
        return (0);
    }

    /**
     * 멀티 스레드 기반
     * 각 클라이언트 소켓 fd 마다 스레드를 생성
     */
    void multi_thread_run()
    {
        int clnt_sock;
        pthread_t thread;

        while (1)
        {
            // client accept
            clnt_sock = accept_server();
            if (clnt_sock == -1)
                continue;
            std::cout << "[client " << clnt_sock << "] Connected!" << std::endl;

            // thread create
            pthread_create(&thread, NULL, client_thread_handling, (void *)&clnt_sock);
            pthread_detach(thread);
        }
        close(socket_fd);
    }

    /**
     * 멀티 플렉싱 기반 방법 1
     * select 사용 :
     *  이벤트(I/O) 별로 감시할 소켓fd 들을 fd_set이라는 파일상태 테이블(fd비트배열)에 등록하고,
     *  등록된 fd에서 이벤트가 발생했을 경우 fd_set을 확인하는 방식으로 동작
     */
    void multi_plexing_run_with_select()
    {
        fd_set reads, reads_tmp; // 파일상태 테이블
        struct timeval timeout;  // timeout 구조체
        int fd_max, fd_num, i;
        int clnt_sock;
        int str_len;
        char message[BUFSIZE];

        FD_ZERO(&reads);            // fd_set 초기화
        FD_SET(socket_fd, &reads);  // 서버 리스닝 소켓 fd_set 테이블에 추가
        fd_max = socket_fd;
        while(1) 
        {
            reads_tmp = reads;
            timeout.tv_sec = 5;
            timeout.tv_usec = 5000;

            // select() 이벤트 감지
            // -1 : 오류 발생
            // 0 : 타임 아웃
            // 1 이상 : 이벤트가 발생한 개수
            if ((fd_num = select(fd_max + 1, &reads_tmp, 0, 0, &timeout)) == -1)
                break;
            if (fd_num == 0)
                continue;
            for (i = 0; i < fd_max + 1; i++) 
            {
                // fd_set 테이블 검사
                if (FD_ISSET(i, &reads_tmp)) 
                {
                    // 서버 리스닝 소켓에서 이벤트 발생 (연결요청)
                    if (i == socket_fd) 
                    {
                        // client accept
                        clnt_sock = accept_server();
                        FD_SET(clnt_sock, &reads);  // 클라이언트 소켓 fd_set 테이블에 추가
                        if (fd_max < clnt_sock)
                            fd_max = clnt_sock;
                        std::cout << "[client " << clnt_sock << "] Connected!" << std::endl;
                    }
                    // 클라이언트 소켓에서 이벤트 발생
                    else 
                    {
                        // read data
                        str_len = read(i, message, BUFSIZE);
                        if (str_len == 0) // 클라이언트 disconnect 요청
                        {
                            FD_CLR(i, &reads); // fd_set 테이블에서 클라이언트 소켓 삭제
                            close(i);
                            std::cout << "[client " << i << "] Disconnected" << std::endl;
                        } 
                        else 
                        {
                            write(i, message, str_len);
                            std::string str(message, str_len);
                            std::cout << "[client " << clnt_sock << "] : " << str << std::endl;
                        }
                    }
                }
            }
        }
        close(socket_fd);
    }

    /**
     * 멀티플렉싱 기반 방법 2
     * poll 사용 :
     *  select()는 timeval 구조체를 사용하여 타임아웃 값을 세팅하지만,
     *  poll()은 타임아웃 기능을 자체 지원
     */
    void multi_plexing_run_with_poll()
    {
        int event_num;
        struct pollfd fds[10];  // poll fd 구조체
        int clnt_sock;
        int str_len;
        char message[BUFSIZE];

        // 서버 리스닝 소켓을 poll fd 구조체 배열에 추가
        fds[0].fd = socket_fd;
        fds[0].events = POLLIN;

        // 나머지 배열요소 초기화
        for (int i = 1; i< 10; i++)
            fds[i].fd = -1;

        while (1)
        {
            // poll() 배열 안에 이벤트 감지
            // -1 : 오류 발생
            // 0 : 타임 아웃
            // 1 이상 : 이벤트 발생한 개수
            event_num = poll(fds, 10, 5000);
            if (event_num == -1)
                break;
            if (event_num == 0)
                continue;

            // 서버 리스닝 소켓 이벤트 감지 (연결 요청)
            if (fds[0].revents == POLLIN)
            {
                // client accept
                clnt_sock = accept_server();
                std::cout << "[client " << clnt_sock << "] Connected!" << std::endl;
                for (int i = 1; i < 10; i++)
                {
                    // poll fd 구조체배열 안에 빈 곳에 클라이언트 소켓 추가
                    if (fds[i].fd < 0)
                    {
                        fds[i].fd = clnt_sock;
                        fds[i].events = POLLIN;
                        break;
                    }
                }
            }

            // 클라이언트 소켓들 이벤트 감지
            for (int i = 1; i < 10; i++)
            {
                if (fds[i].revents < 0)
                    continue;
                
                // 이벤트가 감지되면
                if (fds[i].revents & (POLLIN | POLLPRI))
                {
                    // read 에러이거나 클라이언트 disconnect 요청
                    if ((str_len = read(fds[i].fd, message, BUFSIZE)) == 0)
                    {
                        close(fds[i].fd);
                        std::cout << "[client " << fds[i].fd << "] Disconnected" << std::endl;
                        fds[i].fd = -1;
                        break;
                    }
                    // read data
                    else
                    {
                        write(fds[i].fd, message, str_len);
                        std::string str(message, str_len);
                        std::cout << "[client " << fds[i].fd << "] : " << str << std::endl;
                    }
                }
            }
        }
        close(socket_fd);
    }

    /**
     * 멀티플렉싱 기반 방법 3
     * epoll 사용 :
     *  커널 레벨 멀티플렉싱 지원
     *  커널에 관찰 대상에 대한 정보를 한번만 전달하고, 대상의 범위 또는
     *  내용 변경이 있을 때만 변경사항을 알려줌
     *  리눅스에서는 epoll(), 윈도우에서는 IOCP() 맥에서는 Kqueue() 사용
     */
    void multi_plexing_run_with_epoll()
    {
        int kq, event_num;
        std::vector<struct kevent> change_list; // kqueue에 등록할 event list
        struct kevent event_list[10];           // event 리스트
        struct kevent event_temp;               // event 임시 변수
        struct kevent* curr_event;
        int str_len;
        int clnt_sock;
        char message[BUFSIZE];

        // kqueue 초기화
        if ((kq = kqueue()) == -1)
            throw std::exception();

        // 서버 리스닝 소켓 change list에 추가
        EV_SET(&event_temp, socket_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
        change_list.push_back(event_temp);

        while (1)
        {
            // kevent() change list 안에 이벤트들을 새로 등록하고, 이벤트 발생 감지
            // -1 : 오류 발생
            // 0 : 타임 아웃
            // 1 이상 : 이벤트 발생한 개수
            event_num = kevent(kq, &change_list[0], change_list.size(), event_list, 10, NULL);
            if (event_num == -1)
                break;
            change_list.clear(); // change list 초기화
            for (int i = 0; i < event_num; i++)
            {
                curr_event = &event_list[i];
                // 현재 이벤트가 에러 발생
                if (curr_event->flags & EV_ERROR)
                {
                    if (curr_event->ident == socket_fd)
                        std::exception();
                    else
                    {
                        close(curr_event->ident);
                        std::cout << "[client " << curr_event->ident << "] Disconnected" << std::endl;
                    }
                }
                // 현재 이벤트가 read일 경우
                else if (curr_event->filter == EVFILT_READ)
                {
                    // 서버 리스닝 소켓에서 이벤트 발생
                    if (curr_event->ident == socket_fd)
                    {
                        // client accpet
                        clnt_sock = accept_server();
                        std::cout << "[client " << clnt_sock << "] Connected!" << std::endl;
                        // 클라이언트 소켓 change list에 추가
                        EV_SET(&event_temp, clnt_sock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
                        change_list.push_back(event_temp);
                        EV_SET(&event_temp, clnt_sock, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
                        change_list.push_back(event_temp);
                    }
                    // 클라이언트 소켓에서 이벤트 발생
                    else
                    {
                        // read 에러이거나 클라이언트 disconnect 요청
                        if ((str_len = read(curr_event->ident, message, BUFSIZE)) == 0)
                        {
                            close(curr_event->ident);
                            std::cout << "[client " << curr_event->ident << "] Disconnected" << std::endl;
                        }
                        // read data
                        else
                        {
                            write(curr_event->ident, message, str_len);
                            std::string str(message, str_len);
                            std::cout << "[client " << curr_event->ident << "] : " << str << std::endl;
                        }
                    }
                }
            }
        }
        close(socket_fd);
    }

    public:
    test_server(int port)
    {
        my_port = port;
        if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
        {
            throw std::exception();
        }
    }

    int run()
    {
        bind_server();
        listen_server();
        // multi_process_run();             // 멀티 프로세스 기반 서버
        // multi_thread_run();              // 멀티 스레드 기반 서버
        // multi_plexing_run_with_select(); // 멀티 플렉싱(select) 기반 서버
        // multi_plexing_run_with_poll();   // 멀티 플렉싱(poll) 기반 서버
        multi_plexing_run_with_epoll();     // 멀티 플렉싱(epoll) 기반 서버
        return (0);
    }
};

#endif