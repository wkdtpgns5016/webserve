#include "ServerController.hpp"

ServerController::ServerController() : _request_message()
{

}

// ServerController::ServerController(Server* self) : _self(self), _request_message()
// {
    
// }

ServerController::ServerController(const ServerController& server_controller)
{
    if (this == &server_controller)
        return ;
    // _self = server_controller._self;
    
    _request_message = server_controller._request_message;
}

ServerController::~ServerController()
{

}

ServerController& ServerController::operator=(const ServerController& server_controller)
{
    if (this == &server_controller)
        return (*this);
    // _self = server_controller._self;
    _request_message = server_controller._request_message;
    return (*this);
}

HttpRequestMessage& ServerController::getRequestMessage(void)
{
    return (_request_message);
}

void ServerController::setRequestMessage(const std::string& message)
{
    _request_message = HttpRequestMessage(message);
}

HttpResponseMessage ServerController::getHandler()
{
    StatusLine start_line("HTTP/1.1", 200, "OK");
    std::map<std::string, std::string> headers;
    std::string message_body("This is GET Method");

    HttpResponseMessage response_message(start_line, headers, message_body);
    return (response_message);
}

HttpResponseMessage ServerController::postHandler()
{
    StatusLine start_line("HTTP/1.1", 200, "OK");
    std::map<std::string, std::string> headers;
    std::string message_body("This is POST Method");

    HttpResponseMessage response_message(start_line, headers, message_body);
    return (response_message);
}

HttpResponseMessage ServerController::deleteHandler()
{
    std::cout << "delteHandler()" << std::endl;
    StatusLine start_line("HTTP/1.1", 200, "OK");
    std::map<std::string, std::string> headers;
    std::string message_body("This is DELETE Method");

    HttpResponseMessage response_message(start_line, headers, message_body);
    return (response_message);
}

HttpResponseMessage ServerController::requestHandler()
{
    std::string http_method;
    HttpResponseMessage response_message;

    http_method = _request_message.getStartLine().getHttpMethod();
    if (http_method.compare("GET") == 0)
        response_message = getHandler();
    if (http_method.compare("POST") == 0)
        response_message = postHandler();
    if (http_method.compare("DELETE") == 0)
        response_message = deleteHandler();
    return (response_message);
}
