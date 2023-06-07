#include "WebServer.hpp"
#include <map>

WebServer::WebServer()
{
}

WebServer::~WebServer()
{
    std::map<int, Server *>::iterator ite = _servers.end();
    for (std::map<int, Server *>::iterator it; it != ite ; it++)
		delete (*it).second;
}

int	WebServer::initSocket(int port, unsigned int ip)
{
	int	fd;
	struct	sockaddr_in	addr;
	int	optvalue = 1;

	(void)ip;
	if ((fd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		exit(1);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ip;
	addr.sin_port = htons(port);

	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optvalue, sizeof(optvalue));
	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		exit(1);
	if (listen(fd, 1000) == -1)
		exit(1);
	
	return fd;
}


WebServer::WebServer(const Conf &conf)
{
	ServerBlock* block;
	std::vector<ServerBlock*>	blocks;
	std::pair<int, unsigned int> port_addr;
	int	fd;
	std::map<std::pair<int, unsigned int>, std::vector<ServerBlock*> > server_blocks;

	std::vector<Block*> inner_blocks = conf.getInnerBlock();
	std::vector<Block*>::iterator ite= inner_blocks.end();

	for (std::vector<Block*>::iterator it= inner_blocks.begin(); it != ite; it++)
	{
		port_addr = std::make_pair((*it)->getPort(), (*it)->getAddr());
		block = dynamic_cast<ServerBlock*>(*it);
		server_blocks[port_addr].push_back(block);
	}

	std::map<std::pair<int, unsigned int>, std::vector<ServerBlock*> >::iterator	ite1 = server_blocks.end();
	for(std::map<std::pair<int, unsigned int>, std::vector<ServerBlock*> >::iterator it = server_blocks.begin(); it != ite1; it++)
	{
		port_addr = (*it).first;
		blocks = (*it).second;
		fd = initSocket(port_addr.first, port_addr.second);
		Logger::writeInfoLog(port_addr.first, "Server started", false);
		fcntl(fd, F_SETFL, O_NONBLOCK);
		_servers[fd] = new Server(fd, blocks);
	}
}
void WebServer::change_events(uintptr_t ident, int16_t filter,
                   uint16_t flags, std::vector<struct kevent>  *change_list)
{
    struct kevent temp_event;

    EV_SET(&temp_event, ident, filter, flags, 0, 0, NULL);
    change_list->push_back(temp_event);
}

std::string getAddrString(void * sin_addr)
{
	in_addr* s_addr = reinterpret_cast<in_addr *>(sin_addr);
	std::string str;
	in_addr_t addr = htonl(s_addr->s_addr);
	int size = 24;
	while (size >= 0)
	{
		int n = addr >> size;
		addr -= n << size;
		str += ft::itos(n);
		size -= 8;
		if (size >= 0)
			str += ".";
	}
	return (str);
}

void WebServer::accept_new_client(std::vector<struct kevent> *change_list, int server_socket)
{
    /* accept new client */
    int client_socket;
    socklen_t addr_len;
    struct sockaddr_in addr;

    if ((client_socket = accept(server_socket, (struct sockaddr *)&addr, &addr_len)) == -1)
	{
		Logger::writeErrorLog("Accept error");
        exit(1);
	}

    fcntl(client_socket, F_SETFL, O_NONBLOCK);
	struct linger c_linger;
	c_linger.l_onoff = 1;
	c_linger.l_linger = 0;
	setsockopt(client_socket, SOL_SOCKET, SO_LINGER, &c_linger, sizeof(c_linger));
	std::string str = getAddrString(&addr.sin_addr);
    /* add event for client socket - add read && write event */
    change_events(client_socket, EVFILT_READ, EV_ADD | EV_ENABLE, change_list);
    change_events(client_socket, EVFILT_WRITE, EV_ADD | EV_ENABLE,change_list);

    _servers[server_socket]->accept_new_client(client_socket, str);
	_servers_with_clients[client_socket] = _servers[server_socket];
}


void WebServer::run(void)
{
    int                         _kqueue;
    std::vector<struct kevent>  change_list;
    struct kevent               _event_list[8];
    struct kevent*              _curr_event;


	if ((_kqueue = kqueue()) == -1)
	{
		Logger::writeErrorLog("Kqueue error");
		exit(1);
	}
    /* add event for server socket */
	for (std::map<int, Server*>::iterator it = _servers.begin(); it != _servers.end(); it++)
	{
    	change_events((*it).first, EVFILT_READ, EV_ADD | EV_ENABLE, &change_list);
	}
	 /* main loop */
    int new_events;
    while (1)
    {
        /*  apply changes and return new events(pending events) */
        new_events = kevent(_kqueue, &change_list[0], change_list.size(), _event_list, 8, NULL);
        if (new_events == -1)
		{
			Logger::writeErrorLog("Kevent error");
            exit(1);
		}

        change_list.clear(); // clear change_list for new changes

        for (int i = 0; i < new_events; ++i)
        {
            _curr_event = &_event_list[i];

            /* check error event return */
            if (_curr_event->flags & EV_ERROR)
            {
                if (_servers.count(_curr_event->ident) == 1)
				{
					Logger::writeErrorLog("Server Error");
                    exit(1);
				}
                else
				{
					_servers_with_clients[_curr_event->ident]->disconnect_client(_curr_event->ident);
				}
                    
            }
            else if (_curr_event->filter == EVFILT_READ)
            {
                if (_servers.count(_curr_event->ident) == 1)
				{
					accept_new_client(&change_list, _curr_event->ident);
				}
				else
					_servers_with_clients[_curr_event->ident]->recvMessage(_curr_event->ident);
            }
            else if (_curr_event->filter == EVFILT_WRITE)
            {   
				_servers_with_clients[_curr_event->ident]->sendMessage(_curr_event->ident);
            }
        }
		for (std::map<int, Server*>::iterator it = _servers.begin(); it != _servers.end(); it++)
		{
			(*it).second->checkConnectionTimeout();
		}
        
    }
}
