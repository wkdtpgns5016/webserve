#ifndef SERVER_HPP
#define SERVER_HPP

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

#include "../ServerParser/ServerParser.hpp"
#include "../ServerHandler/ServerHandler.hpp"

#define BUFSIZE 1024

class Server 
{
private:
    pthread_t                   _s_thread;
    int                         _server_socket;
    struct sockaddr_in          _server_addr;
    std::vector<struct kevent>  _change_list;
    struct kevent*              _curr_event;
    std::map<int, std::string>  _clients;
    int                         _kqueue;
    struct kevent               _event_list[8];
    ServerParser                _server_parser;
    
    void socket_init(int port, std::string ip_addr);
    void change_events(uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void *udata);
    void disconnect_client(int client_fd, std::map<int, std::string> &clients);
    void accept_new_client();
    void receiveMessage();
    void sendMessage();

    static void* threadFunction(void *);
public:
    Server();
    Server(std::string block);
    Server(const Server& server);
    ~Server();
    Server& operator=(const Server& server);

    pthread_t getThread(void);
    int  getPort(void);
    void run();
    void threading(void);
};


#endif
