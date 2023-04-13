#ifndef SERVER_HANDLER_HPP
#define SERVER_HANDLER_HPP

#include "../lib/ft/ft.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"

#define HTML_PATH "var/html/"

class ServerHandler
{
    private:
    HttpRequestMessage _request_message;

    HttpResponseMessage getHandler();
    HttpResponseMessage postHandler();
    HttpResponseMessage deleteHandler();

    public:
    ServerHandler();
    ServerHandler(const ServerHandler& server_handler);
    ~ServerHandler();
    ServerHandler& operator=(const ServerHandler& server_handler);

    HttpRequestMessage& getRequestMessage(void);
    void setRequestMessage(const std::string& message);
    HttpResponseMessage requestHandler();
};

#endif