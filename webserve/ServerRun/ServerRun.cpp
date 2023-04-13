#include "ServerRun.hpp"

void ServerRun::socket_init(int &server_socket, struct sockaddr_in &server_addr, int port, std::string ip_addr)
{
    (void)ip_addr;
    if ((server_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        exit(1);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // if (ip_addr.empty())
    //     server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // else
    //     server_addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    server_addr.sin_port = htons(port);
    
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        exit(1);

    if (listen(server_socket, 5) == -1)
        exit(1);
}

void ServerRun::change_events(std::vector<struct kevent> &change_list, uintptr_t ident, int16_t filter,
                   uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
{
    struct kevent temp_event;

    EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
    change_list.push_back(temp_event);
}

void ServerRun::disconnect_client(int client_fd, std::map<int, std::string> &clients)
{
    std::cout << "client disconnected: " << client_fd << std::endl;
    close(client_fd);
    clients.erase(client_fd);
}

void ServerRun::accept_new_client(int server_socket, std::map<int, std::string> &clients, std::vector<struct kevent> &change_list)
{
    /* accept new client */
    int client_socket;
    if ((client_socket = accept(server_socket, NULL, NULL)) == -1)
        exit(1);
    std::cout << "accept new client: " << client_socket << std::endl;
    fcntl(client_socket, F_SETFL, O_NONBLOCK);

    /* add event for client socket - add read && write event */
    change_events(change_list, client_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    change_events(change_list, client_socket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
    clients[client_socket] = "";
}

void ServerRun::receive(std::map<int, std::string> &clients, 
                        struct kevent *curr_event, 
                        ServerHandler *handler)
{
    /* read data from client */
    char buf[1024];
    int n = read(curr_event->ident, buf, sizeof(buf));

    if (n <= 0)
    {
        if (n < 0)
            std::cerr << "client read error!" << std::endl;
        disconnect_client(curr_event->ident, clients);
    }
    else
    {
        buf[n] = '\0';
        clients[curr_event->ident] += buf;
        handler->setRequestMessage(clients[curr_event->ident]);
        HttpResponseMessage message = handler->requestHandler();
        std::string start_line = message.getStartLine().getString() + "\r\n";
        
        write(curr_event->ident, start_line.c_str(), start_line.size());
        // std::cout << "received data from " << curr_event->ident << ": " << clients[curr_event->ident] << std::endl;
    }
}

void ServerRun::send(std::map<int, std::string> &clients, struct kevent *curr_event)
{
    /* send data to client */
    std::map<int, std::string>::iterator it = clients.find(curr_event->ident);
    if (it != clients.end())
    {
        if (clients[curr_event->ident] != "")
        {
            int n;
            if ((n = write(curr_event->ident, clients[curr_event->ident].c_str(), clients[curr_event->ident].size()) == -1))
            {
                std::cerr << "client write error!" << std::endl;
                disconnect_client(curr_event->ident, clients);
            }
            else
                clients[curr_event->ident].clear();
        }
    }
}

void ServerRun::run(ServerParser* parser, ServerHandler *handler)
{
    /* init server socket and listen */
    int server_socket;
    struct sockaddr_in server_addr;

    socket_init(server_socket, server_addr, parser->getPort(), parser->getAddr());
    fcntl(server_socket, F_SETFL, O_NONBLOCK);

    /* init kqueue */
    int kq;
    if ((kq = kqueue()) == -1)
        exit(1);

    std::map<int, std::string> clients;     // map for client socket:data
    std::vector<struct kevent> change_list; // kevent vector for changelist
    struct kevent event_list[8];            // kevent array for eventlist

    /* add event for server socket */
    change_events(change_list, server_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    std::cout << "echo server started" << std::endl;

    /* main loop */
    int new_events;
    struct kevent *curr_event;
    while (1)
    {
        /*  apply changes and return new events(pending events) */
        new_events = kevent(kq, &change_list[0], change_list.size(), event_list, 8, NULL);
        if (new_events == -1)
            exit(1);

        change_list.clear(); // clear change_list for new changes

        for (int i = 0; i < new_events; ++i)
        {
            curr_event = &event_list[i];

            /* check error event return */
            if (curr_event->flags & EV_ERROR)
            {
                if (curr_event->ident == (uintptr_t)server_socket)
                    exit(1);
                else
                {
                    std::cerr << "client socket error" << std::endl;
                    disconnect_client(curr_event->ident, clients);
                }
            }
            else if (curr_event->filter == EVFILT_READ)
            {
                if (curr_event->ident == (uintptr_t)server_socket)
                {
                    accept_new_client(server_socket, clients, change_list);
                }
                else if (clients.find(curr_event->ident) != clients.end())
                {
                    receive(clients, curr_event, handler);
                }
            }
            else if (curr_event->filter == EVFILT_WRITE)
            {
                send(clients, curr_event);
            }
        }
    }
}
