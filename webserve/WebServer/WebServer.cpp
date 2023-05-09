#include "WebServer.hpp"

WebServer::WebServer()
{
}

WebServer::~WebServer()
{
    std::vector<Server *>::iterator iter = _servers.begin();
    for (; iter != _servers.end(); iter++)
    {
        if (*iter != NULL)
        {
            delete (*iter);
            *iter = NULL;
        }
    }
}

WebServer::WebServer(std::string path)
{
    std::string config = ft::readFileIntoString(path);
    Conf conf(config);
    std::vector<Block*> s_blocks = conf.getInnerBlock();
    std::vector<Block*>::iterator iter = s_blocks.begin();
    for (;iter != s_blocks.end(); iter++)
    {
        Server* server = new Server(*iter);
        _servers.push_back(server);
    }
}

void WebServer::run(void)
{
    int last_port = -1;
    std::vector<Server *>::iterator iter = _servers.begin();
    for (; iter != _servers.end(); iter++)
    {
        if ((*iter)->getPort() != last_port)
            (*iter)->threading();
        last_port = (*iter)->getPort();
    }
    iter = _servers.begin();
    for (; iter != _servers.end(); iter++)
    {
        pthread_t tmp = (*iter)->getThread();
        pthread_join(tmp, NULL);
    }
}
