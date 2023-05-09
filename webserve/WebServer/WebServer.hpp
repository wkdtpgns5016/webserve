#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "../lib/ft/ft.hpp"
#include <list>
#include <vector>
#include "../Server/Server.hpp"
#include "../Configuration/Conf/Conf.hpp"
#include "../Configuration/Block/Block.hpp"
#include "../Configuration/ServerBlock/ServerBlock.hpp"
#include "../Configuration/LocationBlock/LocationBlock.hpp"

class WebServer
{
private:
    std::vector<Server *> _servers;
    Conf                  _conf;

public:
    WebServer();
    ~WebServer();
    WebServer(std::string path);

    void run(void);
};

#endif
