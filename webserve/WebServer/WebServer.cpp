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
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//addr.sin_addr.s_addr = ip;
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
		fcntl(fd, F_SETFL, O_NONBLOCK);
		_servers[fd] = new Server(fd, blocks);
	}
}
void WebServer::change_events(uintptr_t ident, int16_t filter,
                   uint16_t flags, std::vector<struct kevent>  change_list)
{
    struct kevent temp_event;

    EV_SET(&temp_event, ident, filter, flags, 0, 0, NULL);
    change_list.push_back(temp_event);
}

void WebServer::run(void)
{
    int                         _kqueue;
    std::vector<struct kevent>  change_list;
    struct kevent               _event_list[8];
    struct kevent*              _curr_event;


	if ((_kqueue = kqueue()) == -1)
		exit(1);
    /* add event for server socket */
	for (std::map<int, Server*>::iterator it = _servers.begin(); it != _servers.end(); it++)
	{
    	change_events((*it).first, EVFILT_READ, EV_ADD | EV_ENABLE, change_list);
	}
	 /* main loop */
    int new_events;
    while (1)
    {
        /*  apply changes and return new events(pending events) */
        new_events = kevent(_kqueue, &change_list[0], change_list.size(), _event_list, 8, NULL);
        if (new_events == -1)
            exit(1);

        change_list.clear(); // clear change_list for new changes

        for (int i = 0; i < new_events; ++i)
        {
            _curr_event = &_event_list[i];

            /* check error event return */
            if (_curr_event->flags & EV_ERROR)
            {
                if (_servers.count(_curr_event->ident) == 1)
                    exit(1);
                else
				{
					_servers_with_clients[_curr_event->ident]->disconnect_client(_curr_event->ident);
				}
                    
            }
            else if (_curr_event->filter == EVFILT_READ)
            {
                if (_servers.count(_curr_event->ident) == 1)
                    _servers[_curr_event->ident]->accept_new_client(_curr_event->ident);
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
