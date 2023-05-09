#ifndef SERVER_CONTROLLER_HPP
#define SERVER_CONTROLLER_HPP

#include "../lib/ft/ft.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"
#include "../Configuration/Conf/Conf.hpp"
#include "../Configuration/Block/Block.hpp"
#include "../Configuration/ServerBlock/ServerBlock.hpp"
#include "../Configuration/LocationBlock/LocationBlock.hpp"
#include <unistd.h>
#include <map>

class ServerHandler
{
    private:
    std::map<int, std::string>  _status;
    HttpRequestMessage          _request_message;
    ServerBlock*                _server_block;

    void init_status();
    bool checkFile(std::string request_target);

    std::vector<std::string> getIndexPath(std::string root, std::string index);
    LocationBlock* findLocationParser(std::vector<Block*> locations, std::string request_target);

    std::string findPath(std::string request_target);
    std::string openFile(std::string request_target);
    std::string executeCgi(std::string request_target);

    HttpResponseMessage getHandler();
    HttpResponseMessage postHandler();
    HttpResponseMessage deleteHandler();

    public:
    ServerHandler();
    ServerHandler(ServerBlock* server_block, std::string http_message);
    ServerHandler(const ServerHandler& server_handler);
    ~ServerHandler();
    ServerHandler& operator=(const ServerHandler& server_handler);

    HttpRequestMessage& getRequestMessage(void);
    HttpResponseMessage getResponseMessage(int status_code, std::string message_body);
    HttpResponseMessage requestHandler();
};

#endif