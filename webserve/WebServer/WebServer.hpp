#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "../lib/ft/ft.hpp"
#include <list>
#include <vector>
#include "../Server/Server.hpp"

class WebServer
{
private:
    std::vector<Server *> _servers;

public:
    WebServer();
    ~WebServer();
    WebServer(std::string path);

    void run(void);
};

#endif
