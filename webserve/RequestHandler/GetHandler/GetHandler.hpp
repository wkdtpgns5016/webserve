#ifndef GETHANDLER_HPP
#define GETHANDLER_HPP

#include "../ServerHandler/ServerHandler.hpp"

class GetHandler : public ServerHandler
{
    private:
    std::string openFile(const std::string& reqeuest_target);
    std::string getAutoIndexPage(const std::string& path, const std::string& request_target);
    std::string getDirectoryList(const std::string& path);
    
    public:
    GetHandler();
    GetHandler(ServerBlock* server_block, const HttpRequestMessage& request_message);
    GetHandler(const GetHandler& get_handler);
    ~GetHandler();
    GetHandler& operator=(const GetHandler& get_handler);

    HttpResponseMessage requestHandler();
};

#endif
