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

#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// kqueue를 위한 헤더파일
#include <sys/event.h>


#include "../Server/Server.hpp"

class WebServer
{
private:
	std::map<int, Server*> _servers;
	std::map<int, Server*> _servers_with_clients;
	WebServer();
	int	initSocket(int port, unsigned int ip_addr);
	void change_events(uintptr_t ident, int16_t filter,
                   uint16_t flags, std::vector<struct kevent> * change_list);
	void accept_new_client(std::vector<struct kevent>*  change_list, int server_socket);



public:
    ~WebServer();
    WebServer(const Conf &conf);


    void run(void);
};

#endif
