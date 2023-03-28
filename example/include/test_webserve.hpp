#ifndef TEST_WEBSERVE_HPP
#define TEST_WEBSERVE_HPP

#include "test_server.hpp"
#include "http_request_message.hpp"
#include <fcntl.h>

#define SEND_MESSAGE_BUFSIZE 1024
#define HTML_PATH "/var/www/html"

class test_webserve : public test_server
{
    private:
    /**
     * GET_handler : 클라이언트가 요청한 GET 방식 요청을 수행하는 핸들러 함수
     * GET 방식 
     * data를 url에 실어서 전송
     */
    void GET_handler(http_request_message hrm, int sock, std::string path) 
    {
        std::string final_path;
        int fd;
        int str_len;
        char data[SEND_MESSAGE_BUFSIZE];

        // version 확인
        if (hrm.header.request_line.version.compare("HTTP/1.0") != 0 && \
            hrm.header.request_line.version.compare("HTTP/1.1") != 0)
            write(sock, "HTTP/1.1 400 Bad Request\n", 25);

        // "빈 path일 경우 /index.html로 리다이렉션"
        if (hrm.header.request_line.url.length() == 1 && \
            !strncmp(hrm.header.request_line.url.c_str(), "/", 1))
            hrm.header.request_line.url = "/index.html";
        
        // html 페이지 path 설정
        final_path = path + hrm.header.request_line.url;

        // html 페이지 path를 찾아 클라이언트에게 전송
        if ((fd = open(final_path.c_str(), O_RDONLY)) != -1)
        {
            send(sock, "HTTP/1.0 200 OK\n\n", 17 ,0);
            while (1)
            {
                str_len = read(fd, data, SEND_MESSAGE_BUFSIZE);
                if (str_len <= 0)
                    break;
                write(sock, data, str_len);
            }
        }
        // html 페이지가 없으면 404 error
        else
            write(sock, "HTTP/1.1 404 Not Fount\n", 23);
    }

    /**
     * POST_handler : 클라이언트에게 받은 데이터를 다시 클라이언트에게 전송하는 핸들러 함수
     * POST 방식 
     * data를 body에 실어서 전송
     */
    void POST_handler(http_request_message hrm, int sock) 
    {
        std::string final_path;
        int str_len;
        char data[SEND_MESSAGE_BUFSIZE];

        // version 확인
        if (hrm.header.request_line.version.compare("HTTP/1.0") != 0 && \
            hrm.header.request_line.version.compare("HTTP/1.1") != 0)
        {
            write(sock, "HTTP/1.1 400 Bad Request\n", 25);
        }

        // html 페이지 path를 찾아 클라이언트에게 전송
        send(sock, "HTTP/1.1 200 OK\n\n", 17, 0);
        write(sock, hrm.body.c_str(), hrm.body.length());
    }

    void request_handler(void *clnt_sock, int str_len, char *message)
    {
        int sock;

        sock = *((int *)clnt_sock);

        // HTTP REQUSET MESSAGE 출력
        std::cout << "-----------Request message from Client-----------" << std::endl;
        std::string str(message, str_len);
        std::cout << str << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;

        // HTTP REQUSET MESSAGE 구조체 초기화
        http_request_message hrm(str);

        // html 페이지 경로
        std::string path(getenv("PWD"));
        path.resize(path.length() - 5);
        path += HTML_PATH;

        // HTTP REQUEST METHOD 종류에 따라 다르게 동작
        if (hrm.header.request_line.method == GET) 
            GET_handler(hrm, sock, path);
	    else if (hrm.header.request_line.method == POST) 
            POST_handler(hrm, sock);

        // 연결 종료
        shutdown(sock, SHUT_RDWR);
        close(sock);
    }

    /**
     * 다중 연결 고려하지 않은 서버
     */
    void simple_run()
    {
        int clnt_sock;
        int str_len;
        char message[BUFSIZE];

        while (1)
        {
            clnt_sock = accept_server();
            if (clnt_sock == -1)
                break ;

            // read data
            // 클라이언트는 서버에게 HTTP REQUSET MESSAGE를 전송
            if ((str_len = read(clnt_sock, message, BUFSIZE)) < 0)
                std::exception();
            
            // request handler
            request_handler(&clnt_sock, str_len, message);

            // 연결 종료
            shutdown(clnt_sock, SHUT_RDWR);
            close(clnt_sock);
        }
        
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
        int clnt_sock;
        int str_len;
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
                        }
                        // read data
                        else
                        {
                            request_handler(&curr_event->ident, str_len, message);
                        }
                    }
                }
            }
        }
        close(socket_fd);
    }

    public:
    test_webserve(int port) : test_server(port) {};

    int run()
    {
        bind_server();
        listen_server();
        // simple_run();                   // 다중 연결 고려하지 않은 웹서버 구동
        multi_plexing_run_with_epoll(); // 멀티 플렉싱 기반 웹서버 구동
        return (0);
    }
};

#endif