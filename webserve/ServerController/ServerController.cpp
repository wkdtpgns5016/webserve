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

HttpResponseMessage ServerController::requestHandler(ServerBlock* server_block, HttpRequestMessage request_message)
{
    HttpResponseMessage response_message;
    std::string http_method = request_message.getStartLine().getHttpMethod();
    ServerHandler *handler = NULL;

    if (http_method == "GET" || http_method == "HEAD")
    {
        handler = new GetHandler(server_block, request_message);
        response_message = handler->requestHandler();
    }
    else if (http_method == "POST")
    {
        handler = new PostHandler(server_block, request_message);
        response_message = handler->requestHandler();
    }
    else if (http_method == "DELETE")
    {
        handler = new DeleteHandler(server_block, request_message);
        response_message = handler->requestHandler();
    }
    else if (http_method == "PUT")
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
