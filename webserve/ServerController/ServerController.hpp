#ifndef SERVER_CONTROLLER_HPP
#define SERVER_CONTROLLER_HPP

#include "../lib/ft/ft.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"

#define HTML_PATH "var/html/"

class ServerController
{
    private:
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
    HttpResponseMessage requestHandler();
};

#endif