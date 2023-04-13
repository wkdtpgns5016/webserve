#ifndef SERVER_HPP
#define SERVER_HPP

#include "../ServerController/ServerController.hpp"
#include "../ServerParser/ServerParser.hpp"
#include "../ServerRun/ServerRun.hpp"
#include <map>

#define BUFSIZE 1024

class ServerModule;
class Server
{
private:
    pthread_t                   _s_thread;
    std::map<std::string, ServerModule *>    _modules;

public:
    Server();
    Server(const Server& obj);
    Server& operator=(const Server& obj);
    ~Server();
    Server(const std::string sBlock);

    ServerModule*   selectModule(std::string key);
    void    insertModule(std::string key, ServerModule* module);
    void    deleteModule(std::string key);

    pthread_t getThread(void);
    int  getPort(void);

    static void *run(void *temp);
    void threading(void);
};


#endif
