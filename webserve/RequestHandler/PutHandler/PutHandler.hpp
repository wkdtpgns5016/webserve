#ifndef PUTHANDLER_HPP
#define PUTHANDLER_HPP

#include "../ServerHandler/ServerHandler.hpp"
#include "fcntl.h"

class PutHandler : public ServerHandler
{
    private:
    int openFile(std::string path);
    void writeFile(int fd, std::string message);
    int putMethod();

    public:
    PutHandler();
    PutHandler(ServerBlock* server_block, HttpRequestMessage request_message);
    PutHandler(const PutHandler& get_handler);
    ~PutHandler();
    PutHandler& operator=(const PutHandler& get_handler);

    HttpResponseMessage requestHandler();
};

#endif