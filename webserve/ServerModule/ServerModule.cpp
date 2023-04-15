#include "ServerModule.hpp"
#include "../Server/Server.hpp"

ServerModule::ServerModule()
{

}

ServerModule::ServerModule(Server* self) : _self(self)
{

}

ServerModule::ServerModule(const ServerModule& server_module)
{
    if (this == &server_module)
        return ;
    _self = server_module._self;
    return ;
}

ServerModule::~ServerModule()
{

}

ServerModule& ServerModule::operator=(const ServerModule& server_module)
{
    if (this == &server_module)
        return (*this);
    _self = server_module._self;
    return (*this);
}
