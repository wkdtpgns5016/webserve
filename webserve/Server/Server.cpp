#include "Server.hpp"

Server::Server() : _s_parser("")
{
}

Server::Server(const Server &obj)
{
    *this = obj;
}

Server &Server::operator=(const Server &obj)
{
    _s_parser = obj._s_parser;
    thread = obj.thread;
    return (*this);
}

Server::Server(const std::string sBlock) : _s_parser(ServerParser(sBlock))
{
}

Server::~Server()
{
}

pthread_t Server::getThread(void)
{
    return (this->thread);
}

int  Server::getPort(void)
{
    return (this->_s_parser.getPort());
}

void *Server::run(void *temp)
{
    ServerParser *s_parser = (ServerParser*)temp;
    ServerRun::run(s_parser->getPort(), s_parser->getAddr());
    // ServerRun::run(8080, _s_parser.getAddr());
    return NULL;
}

void Server::threading(void)
{
    int tid = pthread_create(&thread, NULL, Server::run, (void*)&_s_parser);
    if (tid < 0)
        exit(1);
}
