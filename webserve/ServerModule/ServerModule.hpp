#ifndef SERVER_MODULE_HPP
#define SERVER_MODULE_HPP

class Server;
class ServerModule
{
protected:
    Server* _self;

public:
    ServerModule();
    ServerModule(Server* self);
    ServerModule(const ServerModule& server_module);
    ~ServerModule();
    ServerModule& operator=(const ServerModule& server_module);
};

#endif