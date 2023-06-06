#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "../lib/ft/ft.hpp"
#include <list>
#include <map>
#include <vector>
#include "../Configuration/Conf/Conf.hpp"
#include "../Configuration/Block/Block.hpp"
#include "../Configuration/ServerBlock/ServerBlock.hpp"
#include "../Configuration/LocationBlock/LocationBlock.hpp"

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include "../Server/Server.hpp"
class Server;

class WebServer
{
private:
	std::map<int, Server*> _servers;
	std::map<int, Server*> _servers_with_clients;
	WebServer();
	int	initSocket(int port, unsigned int ip_addr);
public:
    ~WebServer();
    WebServer(const Conf &conf);


    void run(void);
};

#endif
