#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <iostream>
#include <unistd.h>
#include "../HttpMessage/RequestMessageParser.hpp"
#include "../ServerController/ServerController.hpp"
#include "../CommonLogFormat/CommonLogFormat.hpp"

class Connection
{
    private:
    int         _client_fd;
    std::string _client_addr;
    RequestMessageParser _message_parser;

    bool checkMessage();

    public:
    Connection();
    Connection(int client_fd, std::string client_addr);
    Connection(const Connection& connection);
    Connection& operator=(const Connection& connection);
    ~Connection();

    void receiveMessage();
    bool sendMessage(ServerBlock *Server_block);
    std::string getClinetAddr() const;
};

#endif