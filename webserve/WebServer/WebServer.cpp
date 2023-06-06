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

	if ((fd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		exit(1);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
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
	std::map<std::pair<int, unsigned int>, std::vector<ServerBlock*>> server_blocks;

	std::vector<Block*> inner_blocks = conf.getInnerBlock();
	std::vector<Block*>::iterator ite= inner_blocks.end();
	for (std::vector<Block*>::iterator it= inner_blocks.begin(); it != ite; it++)
	{
		port_addr = std::make_pair((*it)->getPort(), (*it)->getAddr());
		block = dynamic_cast<ServerBlock*>(*it);
		server_blocks[port_addr].push_back(block);
	}

	std::map<std::pair<int, unsigned int>, std::vector<ServerBlock*>>::iterator	ite1 = server_blocks.end();
	for(std::map<std::pair<int, unsigned int>, std::vector<ServerBlock*>>::iterator it = server_blocks.begin(); it != ite1; it++)
	{
		port_addr = (*it).first;
		blocks = (*it).second;
		fd = initSocket(port_addr.first, port_addr.second);
		_servers[fd] = new Server(fd, blocks);
	}
}

void WebServer::run(void)
{
}
