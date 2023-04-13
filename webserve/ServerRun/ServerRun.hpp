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

#include "../ServerModule/ServerModule.hpp"

#define BUFSIZE 1024

class Server;
class ServerRun : public ServerModule
{
private:
    int                         _server_socket;
    struct sockaddr_in          _server_addr;
    std::vector<struct kevent>  _change_list;
    struct kevent*              _curr_event;
    std::map<int, std::string>  _clients;
    int                         _kqueue;
    struct kevent               _event_list[8];
    
    void socket_init(int port, std::string ip_addr);
    void change_events(uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void *udata);
    void disconnect_client(int client_fd, std::map<int, std::string> &clients);
    void accept_new_client();
    void receiveMessage();
    void sendMessage();
public:
    ServerRun();
    ServerRun(Server* self);
    ServerRun(const ServerRun&server_run);
    ~ServerRun();
    ServerRun& operator=(const ServerRun&server_run);
    void run();
};


#endif
