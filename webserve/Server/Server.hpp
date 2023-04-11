#ifndef SERVER_HPP
#define SERVER_HPP

#include "../ServerParser/ServerParser.hpp"
#include "../ServerRun/ServerRun.hpp"

#define BUFSIZE 1024

class Server
{
private:
    ServerParser    _s_parser;
    pthread_t       thread;
    // ServerRun       _s_run;

public:
    Server();
    Server(const Server& obj);
    Server& operator=(const Server& obj);
    ~Server();
    Server(const std::string sBlock);

    pthread_t getThread(void);

    static void *run(void *temp);
    void threading(void);
};


#endif
