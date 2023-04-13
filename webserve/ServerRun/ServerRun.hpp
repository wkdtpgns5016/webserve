#ifndef SERVERRUN_HPP
#define SERVERRUN_HPP

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
#include <fcntl.h>
#include <map>
#include <vector>

#include <pthread.h>

// socket을 위한 헤더파일
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// select을 위한 헤더파일
#include <sys/select.h>

// poll을 위한 헤더파일
#include <poll.h>

// kqueue를 위한 헤더파일
#include <sys/event.h>

#include "../Server/Server.hpp"

#define BUFSIZE 1024

class ServerRun
{
private:
    static void socket_init(int &server_socket, struct sockaddr_in &server_addr, int port, std::string ip_addr);
    static void change_events(std::vector<struct kevent> &change_list, uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void *udata);
    static void disconnect_client(int client_fd, std::map<int, std::string> &clients);
    static void accept_new_client(int server_socket, std::map<int, std::string> &clients, std::vector<struct kevent> &change_list);
    static void receiveMessage(std::map<int, std::string> &clients, 
                        struct kevent *curr_event, 
                        ServerHandler *handler);
    static void sendMessage(std::map<int, std::string> &clients, struct kevent *curr_event);
public:
    static void run(ServerParser* parser, ServerHandler *handler);
};


#endif
