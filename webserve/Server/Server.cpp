#include "Server.hpp"

Server::Server() : _server_block()
{

}

Server::Server(ServerBlock* block) : _server_block(block)
{
}

Server::~Server()
{

}

void Server::socket_init(int port, unsigned int ip_addr)
{
    int optvalue = 1;
    
    (void)ip_addr;
    if ((_server_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        exit(1);

    memset(&_server_addr, 0, sizeof(_server_addr));
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // if (ip_addr.empty())
    //     server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // else
    //     server_addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    _server_addr.sin_port = htons(port);
    
    setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR, &optvalue, sizeof(optvalue));
    if (bind(_server_socket, (struct sockaddr *)&_server_addr, sizeof(_server_addr)) == -1)
        exit(1);

    if (listen(_server_socket, 1000) == -1)
        exit(1);
}

void Server::change_events(uintptr_t ident, int16_t filter,
                   uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
{
    struct kevent temp_event;

    EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
    _change_list.push_back(temp_event);
}

void Server::disconnect_client(int client_fd)
{
    close(client_fd);
    _clients.erase(client_fd);
}

void Server::accept_new_client()
{
    /* accept new client */
    int client_socket;
    socklen_t addr_len;
    std::string clinet_ip;
    char buf[1024] = {'\0'};
    struct sockaddr_in addr;

    if ((client_socket = accept(_server_socket, (struct sockaddr *)&addr, &addr_len)) == -1)
        exit(1);

    fcntl(client_socket, F_SETFL, O_NONBLOCK);

    /* add event for client socket - add read && write event */
    change_events(client_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    change_events(client_socket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
    clinet_ip = inet_ntop(AF_INET, &addr.sin_addr, buf, INET_ADDRSTRLEN);
    _clients[client_socket] = Connection(client_socket, std::string(buf));
    Logger::writeInfoLog(_clients[client_socket].getClinetFd(), "Add new Client", false);
}

void Server::checkConnectionTimeout()
{
    for(std::map<int, Connection>::iterator it = _clients.begin() ; it != _clients.end(); ++it)
    {
        if (std::time(NULL) - it->second.getCurrentConnectionTime() > 60)
        {
            Logger::writeInfoLog(it->second.getClinetFd(), "Timeout Connection client", false);
            disconnect_client(it->first);
            break;
        }
    }
}

void Server::run()
{
    int                         _kqueue;
    struct kevent               _event_list[8];
    struct kevent*              _curr_event;

    /* init server socket and listen */
    socket_init(_server_block->getPort(), _server_block->getAddr());
    fcntl(_server_socket, F_SETFL, O_NONBLOCK);

    /* init kqueue */
    if ((_kqueue = kqueue()) == -1)
        exit(1);

    /* add event for server socket */
    change_events(_server_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);

    char buf[1024] = {'\0'};
    std::string server_ip = inet_ntop(AF_INET, &_server_addr.sin_addr, buf, INET_ADDRSTRLEN);
    Logger::writeInfoLog(_server_block->getPort(), "Server started", false);

    /* main loop */
    int new_events;
    while (1)
    {
        /*  apply changes and return new events(pending events) */
        new_events = kevent(_kqueue, &_change_list[0], _change_list.size(), _event_list, 8, NULL);
        if (new_events == -1)
            exit(1);

        _change_list.clear(); // clear change_list for new changes

        for (int i = 0; i < new_events; ++i)
        {
            _curr_event = &_event_list[i];

            /* check error event return */
            if (_curr_event->flags & EV_ERROR)
            {
                if (_curr_event->ident == (uintptr_t)_server_socket)
                    exit(1);
                else
                    disconnect_client(_curr_event->ident);
            }
            else if (_curr_event->filter == EVFILT_READ)
            {
                if (_curr_event->ident == (uintptr_t)_server_socket)
                    accept_new_client();
                else if (_clients.find(_curr_event->ident) != _clients.end())
                {
                    if (!_clients[_curr_event->ident].receiveMessage(_server_block))
                        disconnect_client(_curr_event->ident);
                }
            }
            else if (_curr_event->filter == EVFILT_WRITE)
            {   
                std::map<int, Connection>::iterator it = _clients.find(_curr_event->ident);
                if (it != _clients.end())
                {
                    if (!_clients[_curr_event->ident].sendMessage())
                        disconnect_client(_curr_event->ident);
                }
            }
        }
        checkConnectionTimeout();
    }
}

pthread_t Server::getThread(void)
{
    return (_s_thread);
}

int  Server::getPort(void)
{
    return (_server_block->getPort());
}

void *Server::threadFunction(void *temp)
{
    Server* self = static_cast<Server *>(temp);
    self->run();
    return NULL;
}

void Server::threading(void)
{
    int tid = pthread_create(&_s_thread, NULL, Server::threadFunction, static_cast<void *>(this));
    if (tid < 0)
        exit(1);
}
