#ifndef SERVER_CONTROLLER_HPP
#define SERVER_CONTROLLER_HPP

#include "../lib/ft/ft.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"
#include "../ServerModule/ServerModule.hpp"
#include <map>

#define HTML_PATH "var/html/"

class Server;
class ServerController : public ServerModule
{
    private:
    std::map<int, std::string> _status;
    HttpRequestMessage _request_message;

    void init_status();
    HttpResponseMessage getHandler();
    HttpResponseMessage postHandler();
    HttpResponseMessage deleteHandler();

    public:
    ServerController();
    ServerController(Server* self);
    ServerController(const ServerController& server_handler);
    ~ServerController();
    ServerController& operator=(const ServerController& server_handler);

    HttpRequestMessage& getRequestMessage(void);
    void setRequestMessage(const std::string& message);
    HttpResponseMessage getResponseMessage(int status_code);
    HttpResponseMessage requestHandler();
};

#endif