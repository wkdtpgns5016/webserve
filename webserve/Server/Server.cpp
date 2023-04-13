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
    _s_controller = obj._s_controller;
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

ServerController Server::getServerController(void)
{
    return (_s_controller);
}

void *Server::run(void *temp)
{
    Server *self = (Server *)temp;
    ServerParser parser = self->getServerParser();
    ServerController controller = self->getServerController();
    ServerRun::run(&parser, &controller);
    return NULL;
}

void Server::threading(void)
{
    int tid = pthread_create(&_s_thread, NULL, Server::run, (void*)this);
    if (tid < 0)
        exit(1);
}
