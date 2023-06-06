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
    int                         _server_fd;
    std::map<int, Connection>   _clients;
    std::vector<ServerBlock *>  _configs;
    
    void disconnect_client(int client_fd);
    void accept_new_client(int client_fd);
    void checkConnectionTimeout();

public:
    Server();
    Server(int server_fd, std::vector<ServerBlock *> config);
    Server(const Server& server);
    Server& operator=(const Server& server);
    ~Server();

    void sendMessage(int client_fd);
    void recvMessage(int client_fd);
};

#endif
