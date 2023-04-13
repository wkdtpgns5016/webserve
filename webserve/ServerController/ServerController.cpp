#include "ServerController.hpp"
#include "../Server/Server.hpp"

ServerController::ServerController() : ServerModule(), _request_message()
{
    init_status();
}

ServerController::ServerController(Server* self) : ServerModule(self), _request_message()
{
    init_status();
}

ServerController::ServerController(const ServerController& server_controller)
{
    if (this == &server_controller)
        return ;
    _status = server_controller._status;
    _self = server_controller._self;
    _request_message = server_controller._request_message;
}

ServerController::~ServerController()
{

}

ServerController& ServerController::operator=(const ServerController& server_controller)
{
    if (this == &server_controller)
        return (*this);
    _status = server_controller._status;
    _self = server_controller._self;
    _request_message = server_controller._request_message;
    return (*this);
}

void ServerController::init_status()
{
    _status[100] = "Continue";
    _status[101] = "Switching Protocols";
    _status[200] = "OK";
    _status[201] = "Created";
    _status[202] = "Accepted";
    _status[203] = "Non-Authoritative Information";
    _status[204] = "No Content";
    _status[205] = "Reset Content";
    _status[206] = "Partial Content";
    _status[300] = "Multiple Choices";
    _status[301] = "Moved Permanently";
    _status[302] = "Found";
    _status[303] = "See Other";
    _status[304] = "Not Modified";
    _status[305] = "Use Proxy";
    _status[306] = "(Unused)";
    _status[307] = "Temporary Redirect";
    _status[308] = "Permanent Redirect";
    _status[400] = "Bad Request";
    _status[401] = "Unauthorized";
    _status[402] = "Payment Required";
    _status[403] = "Forbidden";
    _status[404] = "Not Found";
    _status[405] = "Method Not Allowed";
    _status[406] = "Not Acceptable";
    _status[407] = "Proxy Authentication Required";
    _status[408] = "Request Timeout";
    _status[409] = "Conflict";
    _status[410] = "Gone";
    _status[411] = "Length Required";
    _status[412] = "Precondition Failed";
    _status[413] = "Content Too Large";
    _status[414] = "URI Too Long";
    _status[415] = "Unsupported Media Type";
    _status[416] = "Range Not Satisfiable";
    _status[417] = "Expectation Failed";
    _status[418] = "(Unused)";
    _status[421] = "Misdirected Request";
    _status[422] = "Unprocessable Content";
    _status[426] = "Upgrade Required";
    _status[500] = "Internal Server Error";
    _status[501] = "Not Implemented";
    _status[502] = "Bad Gateway";
    _status[503] = "Service Unavailable";
    _status[504] = "Gateway Timeout";
    _status[505] = "HTTP Version Not Supported";
}

HttpRequestMessage& ServerController::getRequestMessage(void)
{
    return (_request_message);
}

void ServerController::setRequestMessage(const std::string& message)
{
    _request_message = HttpRequestMessage(message);
}

HttpResponseMessage ServerController::getResponseMessage(int status_code)
{
    StatusLine start_line = StatusLine(_request_message.getStartLine().getHttpVersion(), status_code, _status[status_code]);
    std::map<std::string, std::string> headers;
    std::string message_body;
    HttpResponseMessage response_message = HttpResponseMessage(start_line, headers, message_body);
    return (response_message);
}

HttpResponseMessage ServerController::getHandler()
{
    int status_code = 200;

    HttpResponseMessage response_message = getResponseMessage(status_code);
    std::string message_body = "GET";
    response_message.setMessageBody(message_body);
    return (response_message);
}

HttpResponseMessage ServerController::postHandler()
{
    int status_code = 200;

    HttpResponseMessage response_message = getResponseMessage(status_code);
    std::string message_body = "POST";
    response_message.setMessageBody(message_body);
    return (response_message);
}

HttpResponseMessage ServerController::deleteHandler()
{
    int status_code = 200;

    HttpResponseMessage response_message = getResponseMessage(status_code);
    std::string message_body = "DELETE";
    response_message.setMessageBody(message_body);
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
