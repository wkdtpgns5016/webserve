#ifndef GETHANDLER_HPP
#define GETHANDLER_HPP

#include "../ServerHandler/ServerHandler.hpp"

class GetHandler : public ServerHandler
{
    private:
    std::string openFile(std::string reqeuest_target);
    std::string getAutoIndexPage(std::string path, std::string request_target);
    std::string getDirectoryList(std::string path);
    
    public:
    GetHandler();
    GetHandler(ServerBlock* server_block, HttpRequestMessage request_message);
    GetHandler(const GetHandler& get_handler);
    ~GetHandler();
    GetHandler& operator=(const GetHandler& get_handler);

    HttpResponseMessage requestHandler();
};

#endif