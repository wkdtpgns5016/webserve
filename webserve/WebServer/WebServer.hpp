#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "../Server/Server.hpp"
#include "../lib/ft/ft.hpp"
#include <list>

class WebServer
{
private:
    std::list<Server> _servers;

public:
    WebServer();
    WebServer(std::string path);

    void run(void);
};

#endif
