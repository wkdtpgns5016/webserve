#ifndef SERVER_HPP
#define SERVER_HPP

#include "../ServerController/ServerController.hpp"
#include "../ServerParser/ServerParser.hpp"
#include "../ServerRun/ServerRun.hpp"

#define BUFSIZE 1024

class ServerParser;
class ServerController;
class ServerRun;
class Server
{
private:
    pthread_t           _s_thread;
    ServerParser*       _s_parser;
    ServerController*   _s_controller;
    ServerRun*          _s_run;

public:
    Server();
    Server(const Server& obj);
    Server& operator=(const Server& obj);
    ~Server();
    Server(const std::string sBlock);

    pthread_t getThread(void);
    ServerParser* getServerParser(void);
    ServerController* getServerController(void);
    ServerRun* getServerRun(void);
    int  getPort(void);

    static void *run(void *temp);
    void threading(void);
};


#endif
