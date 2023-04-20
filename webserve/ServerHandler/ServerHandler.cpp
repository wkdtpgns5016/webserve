#include "ServerHandler.hpp"

ServerHandler::ServerHandler() : _request_message()
{
    init_status();
}

ServerHandler::ServerHandler(ServerParser server_parser)
{
    init_status();
    _server_parser = server_parser;
}
ServerHandler::ServerHandler(const ServerHandler& server_handler)
{
    if (this == &server_handler)
        return ;
    _status = server_handler._status;
    _request_message = server_handler._request_message;
    _server_parser = server_handler._server_parser;
}

ServerHandler::~ServerHandler()
{

}

ServerHandler& ServerHandler::operator=(const ServerHandler& server_controller)
{
    if (this == &server_controller)
        return (*this);
    _status = server_controller._status;
    _request_message = server_controller._request_message;
    return (*this);
}

void ServerHandler::init_status()
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

HttpRequestMessage& ServerHandler::getRequestMessage(void)
{
    return (_request_message);
}

void ServerHandler::setRequestMessage(const std::string& message)
{
    _request_message = HttpRequestMessage(message);
}

HttpResponseMessage ServerHandler::getResponseMessage(int status_code, std::string message_body)
{
    StatusLine start_line = StatusLine(_request_message.getStartLine().getHttpVersion(), status_code, _status[status_code]);
    std::map<std::string, std::string> headers;
    HttpResponseMessage response_message = HttpResponseMessage(start_line, headers, message_body);
    return (response_message);
}

bool ServerHandler::checkFile(std::string request_target)
{
    int len = request_target.length();
    if (request_target.substr(len - 4, 3).compare("php") == 0)
        return (false);
    else if (request_target.substr(len - 4, 3).compare("cgi") == 0)
        return (false);
    else if (request_target.substr(len - 3, 2).compare("pl") == 0)
        return (false);
    else
        return (true);
}

std::string ServerHandler::findPath(std::string request_target)
{
    // ServerParser안에 Location 블록에 따라 file 찾기
    // ServerParser* parser = (ServerParser *)_self->selectModule("ServerParser");
    // std::list<LocationParser> locations = parser->getLocations();

    return("var/html" + request_target);
}

std::string ServerHandler::openFile(std::string request_target)
{
    std::string file_path = findPath(request_target);
    return (ft::readFileIntoString(file_path));
}

std::string ServerHandler::executeCgi(std::string request_target)
{
    std::string file_path = findPath(request_target);
    // fork 후 cgi 실행
    return ("");
}

HttpResponseMessage ServerHandler::getHandler()
{
    int status_code = 200;
    std::string message_body = "GET";
    std::string request_target = _request_message.getStartLine().getRequestTarget();

    if (request_target.compare("/") == 0)
    {
        HttpResponseMessage response_message = getResponseMessage(status_code, message_body);
        return (response_message);
    }

    // 파일인지 cgi인지 검사
    if (checkFile(request_target))
        message_body = openFile(request_target);
    else
        message_body = executeCgi(request_target);
    // 응답 생성
    HttpResponseMessage response_message = getResponseMessage(status_code, message_body);
    return (response_message);
}

HttpResponseMessage ServerHandler::postHandler()
{
    int status_code = 200;
    std::string message_body = "POST";

    HttpResponseMessage response_message = getResponseMessage(status_code, message_body);
    return (response_message);
}

HttpResponseMessage ServerHandler::deleteHandler()
{
    int status_code = 200;
    std::string message_body = "DELETE";

    HttpResponseMessage response_message = getResponseMessage(status_code, message_body);
    return (response_message);
}

HttpResponseMessage ServerHandler::requestHandler()
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