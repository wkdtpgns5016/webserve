#ifndef SERVER_CONTROLLER_HPP
#define SERVER_CONTROLLER_HPP

#include "../lib/ft/ft.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"
#include "../ServerParser/ServerParser.hpp"
#include <map>

class ServerHandler
{
    private:
    std::map<int, std::string>  _status;
    HttpRequestMessage          _request_message;
    ServerParser                _server_parser;

    void init_status();
    bool checkFile(std::string request_target);
    std::string findPath(std::string request_target);
    std::string openFile(std::string request_target);
    std::string executeCgi(std::string request_target);

    HttpResponseMessage getHandler();
    HttpResponseMessage postHandler();
    HttpResponseMessage deleteHandler();

    public:
    ServerHandler();
    ServerHandler(ServerParser server_parser);
    ServerHandler(const ServerHandler& server_handler);
    ~ServerHandler();
    ServerHandler& operator=(const ServerHandler& server_handler);

    HttpRequestMessage& getRequestMessage(void);
    void setRequestMessage(const std::string& message);
    HttpResponseMessage getResponseMessage(int status_code, std::string message_body);
    HttpResponseMessage requestHandler();
};

#endif