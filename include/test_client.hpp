#ifndef TEST_CLIENT_HPP
#define TEST_CLIENT_HPP

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <exception>
#include <unistd.h>
#include <iostream>

#define BUFSIZE 1024

class test_client
{
    private:
    int socket_fd;
    int my_port;
    char* server_ip;
    struct sockaddr_in server_addr;

    void connect_server()
    {
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family=AF_INET;
        server_addr.sin_addr.s_addr=inet_addr(server_ip);
        server_addr.sin_port=htons(my_port);
        if(connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        {
            throw std::exception();
        }
    }

    public:
    test_client(char* addr, int port)
    {
        server_ip = addr;
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
        char* message;
        std::string mesg;

        connect_server();
        while(1) 
        {
            /* 메세지 입력, 전송 */
            std::cout << "전송할 메시지를 입력 하세요 (q to quit) : ";
            std::cin >> mesg;
            if (!mesg.compare("q\n")) 
                break;
            message = (char *)mesg.c_str();
            write(socket_fd, message, strlen(message));
            /* 메세지 수신, 출력 */
            str_len = read(socket_fd, message, strlen(message));
            std::cout << "서버로부터 전송된 메세지 : " << message << std::endl;
        }
        close(socket_fd);
        return (0);
    }
};

#endif