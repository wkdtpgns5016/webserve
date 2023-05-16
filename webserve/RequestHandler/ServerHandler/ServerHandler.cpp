#include "ServerHandler.hpp"
#include <stdio.h>
#include <stdlib.h>

ServerHandler::ServerHandler() : _request_message()
{
    init_status();
}

ServerHandler::ServerHandler(ServerBlock* server_block, HttpRequestMessage request_message)
{
    init_status();
    LocationBlock* location_block = findLocationBlock(server_block->getInnerBlock(), 
                                                      request_message.getStartLine().getRequestTarget());
    _request_message = request_message;
    _config = ConfigDto(*server_block, *location_block);
}

ServerHandler::~ServerHandler()
{

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

std::map<std::string, std::string> ServerHandler::setHeader(int status_code, std::string message_body)
{
    std::map<std::string, std::string> headers;
    std::vector<std::string> t = ft::getTime(time(NULL));

    headers["Server"] = "webserv";
    headers["Date"] = t[0] + ", " + t[2] + " " + t[1] + " " + t[4] + " " + t[3] + " GMT";
    headers["Content-Type"] = "text/html";
    headers["Content-Length"] = ft::itos(message_body.size());
    headers["Connection"] = "keep-alive";
    if (status_code == 405)
    {
        std::string allow;
        std::vector<std::string> config_method = _config.getAllowMethod();
        std::vector<std::string>::iterator it = config_method.begin();
        for(; it != config_method.end(); it++)
            allow += *it + ", ";
        allow.substr(0, allow.length() - 2);
        headers["Allow"] = allow;
    }
    return (headers);
}

HttpResponseMessage ServerHandler::getResponseMessage(int status_code, std::string message_body)
{
    StatusLine start_line = StatusLine(_request_message.getStartLine().getHttpVersion(), status_code, _status[status_code]);
    std::map<std::string, std::string> headers = setHeader(status_code, message_body);
    HttpResponseMessage response_message = HttpResponseMessage(start_line, headers, message_body);
    return (response_message);
}

bool ServerHandler::checkFile(std::string request_target)
{
    int len = request_target.length();
    if (len < 4)
        return (true);
    if (request_target.substr(len - 4, 3).compare("php") == 0)
        return (false);
    else if (request_target.substr(len - 4, 3).compare("cgi") == 0)
        return (false);
    else if (request_target.substr(len - 3, 2).compare("pl") == 0)
        return (false);
    else
        return (true);
}

std::vector<std::string> ServerHandler::getIndexPath(std::string root, std::string index)
{
    std::vector<std::string> index_path;
    std::vector<std::string> indexs;

    if (index.empty())
        return (index_path);

    indexs = ft::splitString(index, " ");
    std::vector<std::string>::iterator it = indexs.begin();
    for (; it != indexs.end(); it++)
    {
        index_path.push_back(root + "/" + *it);
    }
    return (index_path);
}

LocationBlock* ServerHandler::findLocationBlock(std::vector<Block*> locations, std::string request_target)
{
    std::vector<Block*>::iterator it = locations.begin();
    LocationBlock* location;
    for (; it != locations.end(); it++)
    {
        location = (LocationBlock *)(*it);
        std::string url = location->getUrl();
        if (request_target.find(url) == 0)
            break ;
    }
    return (location);
}

void ServerHandler::checkAllowMethod(std::string method)
{
    std::vector<std::string> config_method = _config.getAllowMethod();
    if (std::find(config_method.begin(), config_method.end(), method) == config_method.end())
        throw Error405Exceptnion();
}


bool ServerHandler::checkDirectory(std::string path)
{
    struct stat buf;

    stat(path.c_str(), &buf);
    if(S_ISDIR(buf.st_mode))
        return (true);
    return (false);
}

HttpResponseMessage ServerHandler::getErrorResponse(int status_code)
{
    std::string message_body;
    std::stringstream ss;
    ss << "var/html/error-page/" << status_code << ".html";
    message_body = ft::readFileIntoString(ss.str());
    return (getResponseMessage(status_code, message_body));
}

std::string ServerHandler::findPath(std::string request_target)
{
    std::string root = _config.getRoot();
    std::string index = _config.getIndex();

    // 요청 url
    std::string path = root + request_target;

    // 인덱싱 url
    std::vector<std::string> index_path = getIndexPath(path, index);

    if (access(path.c_str(), F_OK) == -1)
    {
        std::vector<std::string>::iterator it = index_path.begin();
        for (; it != index_path.end(); it++)
        {
            if (access((*it).c_str(), R_OK) == 0)      // 읽기 권한 있을 경우
                return (*it);
            else if (access((*it).c_str(), F_OK) == 0) // 권한이 없을 경우
                throw Error500Exceptnion();
        }
        throw Error404Exceptnion(); // 파일이 없을 경우
    }
    return(path);
}

std::string ServerHandler::executeCgi(std::string request_target)
{
    std::string file_path = findPath(request_target);
    // fork 후 cgi 실행
    return ("");
}

const char* ServerHandler::AutoIndexExceptnion::what() const throw() {
  return "Not Found";
}
const char* ServerHandler::Error404Exceptnion::what() const throw() {
  return "Not Found";
}
const char* ServerHandler::Error405Exceptnion::what() const throw() {
  return "Method Not Allowed";
}
const char* ServerHandler::Error500Exceptnion::what() const throw() {
  return "Internal Server Error";
}
const char* ServerHandler::Error503Exceptnion::what() const throw() {
  return "Service Unavailable";
}