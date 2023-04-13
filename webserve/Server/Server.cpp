#include "Server.hpp"

Server::Server()
 : _s_thread(), _s_parser(new ServerParser()), _s_controller(new ServerController()), _s_run(new ServerRun())
{
    _s_parser->setServer(this);
    _s_controller->setServer(this);
    _s_run->setServer(this);
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
 : _s_thread(), _s_parser(new ServerParser(sBlock)), _s_controller(new ServerController()), _s_run(new ServerRun())
{
    _s_parser->setServer(this);
    _s_controller->setServer(this);
    _s_run->setServer(this);
}

Server::~Server()
{
    if (_s_parser != NULL)
        delete _s_parser;
    if (_s_controller != NULL)
        delete _s_controller;
    if (_s_run != NULL)
        delete _s_run;
}

pthread_t Server::getThread(void)
{
    return (this->_s_thread);
}

int  Server::getPort(void)
{
    return (this->_s_parser->getPort());
}

ServerParser* Server::getServerParser(void)
{
    return (_s_parser);
}

ServerController* Server::getServerController(void)
{
    return (_s_controller);
}

ServerRun* Server::getServerRun(void)
{
    return (_s_run);
}

void *Server::run(void *temp)
{
    Server *self = (Server *)temp;
    self->getServerRun()->run();
    return NULL;
}

void Server::threading(void)
{
    int tid = pthread_create(&_s_thread, NULL, Server::run, (void*)this);
    if (tid < 0)
        exit(1);
}
