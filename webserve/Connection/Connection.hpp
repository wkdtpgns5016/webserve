#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <iostream>
#include <unistd.h>
#include "../HttpMessage/RequestMessageParser.hpp"
#include "../ServerController/ServerController.hpp"
#include "../Log/Logger/Logger.hpp"
#include "../Buffer/Buffer.hpp"

class Connection
{
    private:
    int         _client_fd;
    std::string _client_addr;
    time_t      _current_connection_time;

    RequestMessageParser _message_parser;
    HttpRequestMessage _request;
    HttpResponseMessage _response;
    Buffer      _buffer;
    bool        _complete_respose;
    bool        _start_read;

    bool checkMessage();
    bool checkResponse();
    void makeResponse(ServerBlock *server_block);
    void updateConnectionTime();

    public:
    Connection();
    Connection(int client_fd, std::string client_addr);
    Connection(const Connection& connection);
    Connection& operator=(const Connection& connection);
    ~Connection();

    bool receiveMessage();
    bool sendMessage(ServerBlock *server_block);
    void clearConnection();
    std::string getClinetAddr() const;
    int getClinetFd() const;
    time_t getCurrentConnectionTime() const;
};

#endif