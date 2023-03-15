#ifndef TEST_SERVER_HPP
#define TEST_SERVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <exception>
#include <iostream>

#define BUFSIZE 1024

class test_server
{
    private:
    int socket_fd;
    int my_port;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    void bind_server()
    {
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(my_port);
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        std::cout << server_addr.sin_addr.s_addr << std::endl;
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
        int clnt_addr_size;
        clnt_addr_size = sizeof(client_addr);
        return (accept(socket_fd, (struct sockaddr*)&client_addr, (socklen_t *)&clnt_addr_size));
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
        int clnt_sock;
        int str_len;
        char message[BUFSIZE];

        bind_server();
        listen_server();
        clnt_sock = accept_server();
        while( (str_len = read(clnt_sock, message, BUFSIZE)) != 0)
        {
            write(clnt_sock, message, str_len);
            write(1, message, str_len);
            str_len=read(clnt_sock, message, BUFSIZE-1);
            message[str_len]=0;
            printf("서버로부터 전송된 메시지 : %s \n", message);
        }
        close(clnt_sock);
        return (0);
    }
};

#endif