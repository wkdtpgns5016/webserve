#include "Server.hpp"
#include "../ServerModule/ServerModule.hpp"

Server::Server() : _s_thread()
{
    ServerModule* parser = new ServerParser(this);
    ServerModule* controller = new ServerController(this);
    ServerModule* run = new ServerRun(this);

    insertModule("ServerParser", parser);
    insertModule("ServerController", controller);
    insertModule("ServerRun", run);
}

Server::Server(const Server &obj)
{
    *this = obj;
}

Server &Server::operator=(const Server &obj)
{
    _modules = obj._modules;
    _s_thread = obj._s_thread;
    return (*this);
}

Server::Server(const std::string sBlock) : _s_thread()
{
    ServerModule* parser = new ServerParser(sBlock, this);
    ServerModule* controller = new ServerController(this);
    ServerModule* run = new ServerRun(this);

    insertModule("ServerParser", parser);
    insertModule("ServerController", controller);
    insertModule("ServerRun", run);
}

Server::~Server()
{
    std::map<std::string, ServerModule *>::iterator iter = _modules.begin();
    for (; iter != _modules.end(); iter++)
    {
        ServerModule* module = (*iter).second;
        if (module != NULL)
        {
            delete module;
            module = NULL;
        }
    }
}
ServerModule*   Server::selectModule(std::string key)
{
    return ((*(_modules.find(key))).second);
}

void    Server::insertModule(std::string key, ServerModule* module)
{
    if (!_modules.count(key))
        _modules[key] = module;
}

void    Server::deleteModule(std::string key)
{
    if (_modules.count(key))
        _modules.erase(key);
}

pthread_t Server::getThread(void)
{
    return (this->_s_thread);
}

int  Server::getPort(void)
{
    ServerParser* parser = (ServerParser *)selectModule("ServerParser");
    return (parser->getPort());
}

// ServerParser* Server::getServerParser(void)
// {
//     ServerModule* module = selectModule("ServerParser");
//     return ((ServerParser *)module);
// }

// ServerController* Server::getServerController(void)
// {
//     ServerModule* module = selectModule("ServerController");
//     return ((ServerController *)module);
// }

// ServerRun* Server::getServerRun(void)
// {
//     ServerModule* module = selectModule("ServerRun");
//     return ((ServerRun *)module);
// }

void *Server::run(void *temp)
{
    Server* self = (Server *)temp;
    ServerRun* run_module = (ServerRun *)self->selectModule("ServerRun");
    run_module->run();
    return NULL;
}

void Server::threading(void)
{
    int tid = pthread_create(&_s_thread, NULL, Server::run, (void*)this);
    if (tid < 0)
        exit(1);
}
