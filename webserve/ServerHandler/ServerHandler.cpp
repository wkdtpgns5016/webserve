#include "ServerHandler.hpp"

ServerHandler::ServerHandler() : _request_message()
{

}

// ServerHandler::ServerHandler(Server* self) : _self(self), _request_message()
// {
    
// }

ServerHandler::ServerHandler(const ServerHandler& server_handler)
{
    if (this == &server_handler)
        return ;
    // _self = server_handler._self;
    
    _request_message = server_handler._request_message;
}

ServerHandler::~ServerHandler()
{

}

ServerHandler& ServerHandler::operator=(const ServerHandler& server_handler)
{
    if (this == &server_handler)
        return (*this);
    // _self = server_handler._self;
    _request_message = server_handler._request_message;
    return (*this);
}

HttpRequestMessage& ServerHandler::getRequestMessage(void)
{
    return (_request_message);
}

void ServerHandler::setRequestMessage(const std::string& message)
{
    std::cout << "setReqeustMessage()" << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << message << std::endl;
    std::cout << "===========================" << std::endl;
    _request_message = HttpRequestMessage(message);
    std::cout << "HttpRequestMessage()" << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << _request_message.getString() << std::endl;
    std::cout << "===========================" << std::endl;

}

HttpResponseMessage ServerHandler::getHandler()
{
    std::cout << "getHandler()" << std::endl;
    StatusLine start_line("HTTP/1.1", 200, "OK");
    std::map<std::string, std::string> headers;
    std::string message_body("This is GET Method");

    HttpResponseMessage response_message(start_line, headers, message_body);

    return (response_message);
}

HttpResponseMessage ServerHandler::postHandler()
{
    StatusLine start_line("HTTP/1.1", 200, "OK");
    std::map<std::string, std::string> headers;
    std::string message_body("This is POST Method");

    HttpResponseMessage response_message(start_line, headers, message_body);
    return (response_message);
}

HttpResponseMessage ServerHandler::deleteHandler()
{
    StatusLine start_line("HTTP/1.1", 200, "OK");
    std::map<std::string, std::string> headers;
    std::string message_body("This is DELETE Method");

    HttpResponseMessage response_message(start_line, headers, message_body);
    return (response_message);
}

HttpResponseMessage ServerHandler::requestHandler()
{
    std::string http_method;
    HttpResponseMessage response_message;

    std::cout << "requestHandler()" << std::endl;
    http_method = _request_message.getStartLine().getHttpMethod();
    std::cout << http_method << std::endl;
    if (http_method.compare("GET") == 0)
        response_message = getHandler();
    if (http_method.compare("POST") == 0)
        response_message = postHandler();
    if (http_method.compare("DELETE") == 0)
        response_message = deleteHandler();
    return (response_message);
}
