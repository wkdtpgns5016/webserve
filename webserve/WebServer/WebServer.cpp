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
    std::vector<std::string> sBlocks = ft::splitBlockString(config);

    for (unsigned int i = 0; i < sBlocks.size(); i++)
    {
        Server* server = new Server(sBlocks[i]);
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
