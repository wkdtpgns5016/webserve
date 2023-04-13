#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "../Server/Server.hpp"
#include "../lib/ft/ft.hpp"
#include <list>
#include <vector>
class WebServer
{
private:
    std::vector<Server *> _servers;

public:
    WebServer();
    WebServer(std::string path);

    void run(void);
};

#endif
