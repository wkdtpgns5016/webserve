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

#include "../Connection/Connection.hpp"
#include "../Log/Logger/Logger.hpp"

#define BUFSIZE 1024

class Server 
{
private:
    pthread_t                   _s_thread;
    ServerBlock*                _server_block;

    int                         _server_socket;
    struct sockaddr_in          _server_addr;

    std::vector<struct kevent>  _change_list;
    struct kevent*              _curr_event;
    std::map<int, Connection>   _clients;
    int                         _kqueue;
    struct kevent               _event_list[8];
    
    void socket_init(int port, unsigned int ip_addr);
    void change_events(uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void *udata);
    void disconnect_client(int client_fd, std::map<int, Connection> &clients);
    void accept_new_client();

    void checkConnectionTimeout();

    static void* threadFunction(void *);

    Server(const Server& server);
    Server& operator=(const Server& server);
public:
    Server();
    Server(ServerBlock* block);
    ~Server();

    pthread_t getThread(void);
    int  getPort(void);
    void run();
    void threading(void);
};


#endif
