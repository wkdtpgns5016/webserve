#ifndef SERVER_CONTROLLER_HPP
#define SERVER_CONTROLLER_HPP

#include "../lib/ft/ft.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"
#include "../Server/Server.hpp"

#define HTML_PATH "var/html/"

class Server;
class ServerController
{
    private:
    Server*            _self;
    HttpRequestMessage _request_message;

    HttpResponseMessage getHandler();
    HttpResponseMessage postHandler();
    HttpResponseMessage deleteHandler();

    public:
    ServerController();
    ServerController(const ServerController& server_handler);
    ~ServerController();
    ServerController& operator=(const ServerController& server_handler);

    HttpRequestMessage& getRequestMessage(void);
    void setRequestMessage(const std::string& message);
    void setServer(Server* server);
    HttpResponseMessage requestHandler();

};

#endif