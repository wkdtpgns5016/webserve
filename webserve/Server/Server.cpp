#include "Server.hpp"

Server::Server() : _s_thread(), _s_parser("")
{
}

Server::Server(const Server &obj)
{
    *this = obj;
}

Server &Server::operator=(const Server &obj)
{
    _s_thread = obj._s_thread;
    _s_parser = obj._s_parser;
    _s_handler = obj._s_handler;
    return (*this);
}

Server::Server(const std::string sBlock)
 : _s_thread(), _s_parser(ServerParser(sBlock))
{
}

Server::~Server()
{
}

pthread_t Server::getThread(void)
{
    return (this->_s_thread);
}

int  Server::getPort(void)
{
    return (this->_s_parser.getPort());
}

ServerParser Server::getServerParser(void)
{
    return (_s_parser);
}

ServerHandler Server::getServerHandler(void)
{
    return (_s_handler);
}

void *Server::run(void *temp)
{
    Server *self = (Server *)temp;
    ServerParser parser = self->getServerParser();
    ServerHandler handler = self->getServerHandler();
    ServerRun::run(&parser, &handler);
    return NULL;
}

void Server::threading(void)
{
    int tid = pthread_create(&_s_thread, NULL, Server::run, (void*)this);
    if (tid < 0)
        exit(1);
}
