#include "ServerController.hpp"

ServerController::ServerController()
{

}

ServerController::ServerController(const ServerController& server_controller)
{
    (void)server_controller;
}

ServerController::~ServerController()
{

}

ServerController& ServerController::operator=(const ServerController& server_controller)
{
    (void)server_controller;
    return (*this);
}

HttpResponseMessage ServerController::requestHandler(ServerBlock* server_block, const std::string& http_message)
{
    std::string msg = http_message;
    
    // 임시 1
    if (http_message.compare("GET /directory/youp") == 0)
        msg = "GET /directory/youpi.bad_extension HTTP/1.1";
    else if (http_message.compare("GET /directo") == 0)
        msg = "GET /directory/oulalala HTTP/1.1";
    else if (http_message.compare("GET /direct") == 0)
        msg = "GET /directory/nop/other.pouic HTTP/1.1";
    else if (http_message.compare("G") == 0)
        msg = "GET /directory/nop/other.pouac HTTP/1.1";

    HttpRequestMessage request_message(msg);
    HttpResponseMessage response_message;
    std::string http_method = request_message.getStartLine().getHttpMethod();
    ServerHandler *handler = NULL;

    if (http_method.compare("GET") == 0)
    {
        handler = new GetHandler(server_block, request_message);
        response_message = handler->requestHandler();
    }
    else if (http_method.compare("POST") == 0)
    {
        handler = new PostHandler(server_block, request_message);
        response_message = handler->requestHandler();
    }
    else if (http_method.compare("DELETE") == 0)
    {
        handler = new DeleteHandler(server_block, request_message);
        response_message = handler->requestHandler();
    }
    else if (http_method.compare("PUT") == 0)
    {
        handler = new PutHandler(server_block, request_message);
        response_message = handler->requestHandler();
    }
    else
    {
        handler = new GetHandler(server_block, request_message);
        response_message = handler->requestHandler();
    }
    if (handler != NULL)
        delete handler;
    return (response_message);
}
