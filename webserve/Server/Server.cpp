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

void Server::socket_init(int port, std::string ip_addr)
{
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
    
    if (bind(_server_socket, (struct sockaddr *)&_server_addr, sizeof(_server_addr)) == -1)
        exit(1);

    if (listen(_server_socket, 5) == -1)
        exit(1);
}

void Server::change_events(uintptr_t ident, int16_t filter,
                   uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
{
    struct kevent temp_event;

    EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
    _change_list.push_back(temp_event);
}

void Server::disconnect_client(int client_fd, std::map<int, std::string> &clients)
{
    // std::cout << "client disconnected: " << client_fd << std::endl;
    close(client_fd);
    clients.erase(client_fd);
}

void Server::accept_new_client()
{
    /* accept new client */
    int client_socket;
    if ((client_socket = accept(_server_socket, NULL, NULL)) == -1)
        exit(1);
    // std::cout << "accept new client: " << client_socket << std::endl;
    fcntl(client_socket, F_SETFL, O_NONBLOCK);

    /* add event for client socket - add read && write event */
    change_events(client_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    change_events(client_socket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
    _clients[client_socket] = "";
}

void Server::receiveMessage()
{
    /* read data from client */
    char buf[1024];
    int n = read(_curr_event->ident, buf, sizeof(buf));

    if (n <= 0)
    {
        if (n < 0)
            std::cerr << "client read error!" << std::endl;
    }
    else
    {
        buf[n] = '\0';
        _clients[_curr_event->ident] += buf;
    }
    // /* read data from client */
    // char buf[10000];
    // int n;
    // // std::string msg;
    // // while ((n = read(_curr_event->ident, buf, sizeof(buf))) > 0)
    // // {
    // //     buf[n] = '\0';
    // //     msg += buf;
    // // }
    // // _clients[_curr_event->ident] += msg;
    // // std::cout << "\n-------------------------------------------------" << std::endl;
    // // std::cout << "resived: " << _clients[_curr_event->ident] << std::endl;
    // // std::cout << "-------------------------------------------------\n" << std::endl;
    // // ServerController controller;
    // // HttpRequestMessage request_message(_clients[_curr_event->ident]);
    // // HttpResponseMessage message = controller.requestHandler(_server_block, _clients[_curr_event->ident]);
    // // write(_curr_event->ident, message.getString().c_str(), message.getString().size());
    // // disconnect_client(_curr_event->ident, _clients);
    // // CommonLogFormat log = CommonLogFormat(request_message, message);
    // // log.wirteLogMessage(1);
    // n = read(_curr_event->ident, buf, sizeof(buf));
    // if (n <= 0)
    // {
    //     if (n < 0)
    //         std::cerr << "client read error!" << std::endl;
    //     disconnect_client(_curr_event->ident, _clients);
    // }
    // else
    // {
    //     _clients[_curr_event->ident] += buf;
    //     std::cout << "\n-------------------------------------------------" << std::endl;
    //     std::cout << "resived: " << _clients[_curr_event->ident] << std::endl;
    //     std::cout << "-------------------------------------------------\n" << std::endl;
    //     ServerController controller;
    //     HttpRequestMessage request_message(_clients[_curr_event->ident]);
    //     HttpResponseMessage message = controller.requestHandler(_server_block, _clients[_curr_event->ident]);
    //     write(_curr_event->ident, message.getString().c_str(), message.getString().size());
    //     disconnect_client(_curr_event->ident, _clients);
    //     CommonLogFormat log = CommonLogFormat(request_message, message);
    //     log.wirteLogMessage(1);
    // }
}

void Server::sendMessage()
{
    /* send data to client */
    std::map<int, std::string>::iterator it = _clients.find(_curr_event->ident);
    if (it != _clients.end())
    {
        if (_clients[_curr_event->ident] != "")
        {
            ServerController controller;
            HttpRequestMessage request_message(_clients[_curr_event->ident]);
            HttpResponseMessage message = controller.requestHandler(_server_block, _clients[_curr_event->ident]);
            write(_curr_event->ident, message.getString().c_str(), message.getString().size());
            disconnect_client(_curr_event->ident, _clients);
            CommonLogFormat log = CommonLogFormat(request_message, message);
            log.wirteLogMessage(1);
        }
    }
}

void Server::run()
{
    /* init server socket and listen */
    socket_init(_server_block->getPort(), _server_block->getAddr());
    fcntl(_server_socket, F_SETFL, O_NONBLOCK);

    /* init kqueue */
    if ((_kqueue = kqueue()) == -1)
        exit(1);

    /* add event for server socket */
    change_events(_server_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);

    std::string msg = "Server started [" + ft::itos(_server_block->getPort()) + "]";
    std::cout << msg << std::endl;

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
                {
                    std::cerr << "client socket error" << std::endl;
                    disconnect_client(_curr_event->ident, _clients);
                }
            }
            else if (_curr_event->filter == EVFILT_READ)
            {
                if (_curr_event->ident == (uintptr_t)_server_socket)
                    accept_new_client();
                else if (_clients.find(_curr_event->ident) != _clients.end())
                    receiveMessage();
            }
            else if (_curr_event->filter == EVFILT_WRITE)
                sendMessage();
        }
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
