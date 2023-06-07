#include "ServerHandler.hpp"
#include <stdio.h>
#include <stdlib.h>

ServerHandler::ServerHandler() : _request_message()
{
    init_status();
}

ServerHandler::ServerHandler(ServerBlock* server_block, const HttpRequestMessage& request_message)
{
    init_status();
    LocationBlock* location_block = findLocationBlock(server_block->getInnerBlock(), 
                                                      request_message.getStartLine().getRequestTarget());
    _request_message = request_message;
    _config = ConfigDto(server_block, location_block);
}

ServerHandler::~ServerHandler()
{

}

ServerHandler::ServerHandler(const ServerHandler& server_handler)
{
    _status = server_handler._status;
    _request_message = server_handler._request_message;
    _config = server_handler._config;

}

ServerHandler& ServerHandler::operator=(const ServerHandler& server_handler)
{
    _status = server_handler._status;
    _request_message = server_handler._request_message;
    _config = server_handler._config;
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

const HttpRequestMessage& ServerHandler::getRequestMessage(void)
{
    return (_request_message);
}

std::map<std::string, std::string> ServerHandler::setHeader(int status_code, const std::string& message_body, const std::map<std::string, std::string>& cgi_header)
{
    std::map<std::string, std::string> headers;
    std::vector<std::string> t = ft::getTime(time(NULL));

    headers["Server"] = "webserv";
    headers["Date"] = t[0] + ", " + t[2] + " " + t[1] + " " + t[4] + " " + t[3] + " GMT";
    if (cgi_header.find("Content-Type") != cgi_header.end())
        headers["Content-Type"] = cgi_header.at("Content-Type");
    else
        headers["Content-Type"] = "text/html";
    headers["Content-Length"] = ft::itos(message_body.size());
    if (_request_message.checkConnectionClose())
        headers["Connection"] = "close";
    else
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

HttpResponseMessage ServerHandler::getResponseMessage(int status_code, const std::string& message_body, const std::map <std::string, std::string>& cgi_header)
{
    std::vector<std::string> arr;
    StatusLine start_line = StatusLine("HTTP/1.1", status_code, _status[status_code]);
    std::map<std::string, std::string> headers = setHeader(status_code, message_body, cgi_header);
    if (_request_message.getHttpMethod() == "HEAD")
		HttpResponseMessage response_message = HttpResponseMessage(start_line, headers, "");
    HttpResponseMessage response_message = HttpResponseMessage(start_line, headers, message_body);
    return (response_message);
}

int ServerHandler::checkFile(const std::string& request_target)
{
    std::map<std::string, std::string> cgi_config;
    cgi_config = _config.getCgiConfig();

    size_t pos = request_target.rfind('.');
    if (pos == std::string::npos)
        return (-1);
    if (request_target.length() < 4)
        return (-1);
    std::string extension = request_target.substr(pos);
    if (cgi_config.find(extension) == cgi_config.end())
        return (-1);
    return (1);
}

HttpResponseMessage ServerHandler::redirectionHttpMessage()
{
    int status;
    StatusLine start_line;
    std::map<std::string, std::string> header;
    std::map<std::string, std::string> cgi_header;
    std::string message_body;
    HttpResponseMessage response;

    // 임시 
    std::pair<int, std::string> return_value = _config.getReturnValue();
    status = return_value.first;
    start_line = StatusLine(_request_message.getHttpVersion(), status, _status[status]);

    if (status >= 300 && status < 400)
    {
        header = setHeader(status, message_body, cgi_header);
        header["Location"] = return_value.second;
        return (HttpResponseMessage(start_line, header, message_body));
    }
    else
    {
        message_body = return_value.second;
        if (message_body.at(0) == '\"')
            message_body = message_body.substr(1, message_body.length() - 2);
        header = setHeader(status, message_body, cgi_header);
        return (HttpResponseMessage(start_line, header, message_body));
    }
}

std::vector<std::string> ServerHandler::getIndexPath(const std::string& root, const std::string& index)
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

LocationBlock* ServerHandler::findLocationBlock(const std::vector<Block*>& locations, const std::string& request_target)
{
    std::vector<Block*>::const_iterator it = locations.begin();
    LocationBlock* location = NULL;
    LocationBlock* temp = NULL;
    int find_flag;
    for (; it != locations.end(); it++)
    {
        location = (LocationBlock *)(*it);
        std::string url = cleanUrl(location->getUrl(), false);
        std::string compare_url = cleanUrl(request_target, true);
        if (url.compare(compare_url.substr(0, url.length())) == 0)
        {
            find_flag = 1;
            if (url.compare("/") == 0)
            {
                temp = location;
                find_flag = 0;
                continue;
            }
            break ;
        }

    }
    if (find_flag == 0)
        return (temp);
    return (location);
}

std::string ServerHandler::cleanUrl(const std::string& url, bool request_target)
{
    std::vector<std::string> url_arr = ft::splitString(url, "/");
    std::vector<std::string>::iterator it = url_arr.begin();
    std::string new_url;

    if (url == "/")
        return (url);
    for (; it != url_arr.end(); it++)
    {
        new_url = new_url + "/" + *it;
    }
    if (url.back() == '/' && request_target)
        new_url += "/";
    return (new_url);
}

void ServerHandler::checkAllowMethod(const std::string& method)
{
    std::vector<std::string> config_method = _config.getAllowMethod();
    if (std::find(config_method.begin(), config_method.end(), method) == config_method.end())
        throw Error405Exceptnion();
}


bool ServerHandler::checkDirectory(const std::string& path)
{
    struct stat buf;

    stat(path.c_str(), &buf);
    if(FT_ISDIR(buf.st_mode))
        return (true);
    return (false);
}

void ServerHandler::throwStatusError(int status_code)
{
    switch (status_code)
    {
    case 400:
        throw Error400Exceptnion();
        break;
    case 404:
        throw Error404Exceptnion();
        break;
    case 405:
        throw Error405Exceptnion();
        break;
    case 413:
        throw Error413Exceptnion();
        break;
    case 500:
        throw Error500Exceptnion();
        break;
    case 503:
        throw Error503Exceptnion();
        break;
    default:
        break;
    }
}

HttpResponseMessage ServerHandler::getErrorResponse(int status_code)
{
    std::string message_body = ft::itos(status_code) + " " + _status[status_code];
    std::map<std::string, std::string> cgi_header;
    if (_config.getDefaultErrorPage().empty())
        return (getResponseMessage(status_code, message_body, cgi_header));

    std::vector<std::string> arr = ft::splitString(_config.getDefaultErrorPage(), " ");
    std::vector<std::string>::iterator it = arr.begin();
    std::string status = ft::itos(status_code);
    std::string path;

    for (; it != arr.end() - 1; it++)
    {
        if (status == *it)
        {
            path = _config.getRoot() + arr.back();
            break;
        }
    }
    if (!path.empty())
        message_body = ft::readFileIntoString(path);
    return (getResponseMessage(status_code, message_body, cgi_header));
}


std::string ServerHandler::tryFiles(const std::vector<std::string>& try_files)
{
    std::vector<std::string>::const_iterator it = try_files.begin();
    std::string path;
    for (; it != try_files.end(); it++)
    {
        try
        {
            path = findPath(*it);
            if (!path.empty())
                break;
        }
        catch(...)
        {
            continue;
        }
        
    }
    if (path.empty())
        throw Error404Exceptnion();
    return (path);
}

std::string ServerHandler::findPath(const std::string& request_target)
{
    std::string root = _config.getRoot();
    std::string index = _config.getIndex();

    // 요청 url
    std::string change;
    std::string clean_request_target = cleanUrl(request_target, false);
    if (_config.getUrl().empty() || _config.getUrl() == "/")
        change = clean_request_target;
    else
        change = clean_request_target.substr(_config.getUrl().length());
    std::string path = root + change;

    // 인덱싱 url
    std::vector<std::string> index_path = getIndexPath(path, index);

    std::string directory = path;
    if (directory.back() != '/')
        directory = path + "/";
    if (access(path.c_str(), F_OK) == -1)
    {
        throw Error404Exceptnion();
    }
    else if (access(directory.c_str(), F_OK) != -1)
    {
        if (_config.getAutoindex())
            return (directory);
        std::vector<std::string>::iterator it = index_path.begin();
        for (; it != index_path.end(); it++)
        {
            if (access((*it).c_str(), R_OK) == 0)      // 읽기 권한 있을 경우
                return (*it);
            else if (access((*it).c_str(), F_OK) == 0) // 권한이 없을 경우
                throw Error403Exceptnion();
        }
    }
    return(path);
}

void ServerHandler::checkHttpVersion(const RequestLine& start_line)
{
    std::string http_version = start_line.getHttpVersion();
    std::vector<std::string> arr = ft::splitString(http_version, "/");

    if (http_version.empty())
    {
        _request_message.setStartLine(RequestLine(start_line.getHttpMethod(), 
                                                  start_line.getRequestTarget(), 
                                                  "HTTP/1.1"));
        return ;
    }
    if (arr.size() != 2)
        throw Error400Exceptnion();
    if (arr[0] != "HTTP")
        throw Error400Exceptnion();
    if (arr[1] != "1.0" && arr[1] != "1.1")
        throw Error400Exceptnion();
}

void ServerHandler::checkMessageSize(void)
{
    size_t message_size = _request_message.getMessageSize();
    size_t client_max_body_size = _config.getClientMaxBodySize();
    
    if (message_size > client_max_body_size)
        throw Error413Exceptnion();
}

void ServerHandler::checkUrlSize(void)
{
    size_t message_size = _request_message.getReqeustTarget().length();
    if (message_size > 8000)
        throw Error414Exceptnion();
}

void ServerHandler::checkHttpMessage(void)
{
    // check start line
    RequestLine start_line = _request_message.getStartLine();
    checkAllowMethod(start_line.getHttpMethod());
    checkHttpVersion(start_line);
    checkUrlSize();
    // check message size
    checkMessageSize();
}

std::string ServerHandler::executeCgi(const std::string& file_path)
{
    CGI cgi(_config, _request_message);
    std::string script_name;
    std::string result;

    std::map<std::string, std::string> cgi_config;
    cgi_config = _config.getCgiConfig();

    size_t pos = file_path.rfind('.');
    std::string extension = file_path.substr(pos);
    std::map<std::string, std::string>::iterator it = cgi_config.find(extension);
    if (it == cgi_config.end())
        throw Error422Exceptnion();
    script_name = (*it).second;
    if ((*it).first != ".bla")
        script_name += " " + file_path;
    result = cgi.excute(script_name);
    return (result);
}

HttpResponseMessage ServerHandler::getCgiResponse(int status, const std::string& message_body)
{
    int cgi_status;
    std::map<std::string, std::string> cgi_header;
    std::string cgi_header_str;
    std::string body;
    size_t pos;

    pos = message_body.find("\r\n\r\n");
    if (pos == std::string::npos)
        return (getResponseMessage(status, message_body, cgi_header));
    cgi_header_str = message_body.substr(0, pos);
    cgi_header = getCgiHeader(cgi_header_str);
    body = message_body.substr(pos + 4);
    if ((cgi_status = getStautsCgi(cgi_header)) > 0)
        status = cgi_status;
    throwStatusError(status);
    return (getResponseMessage(status, body, cgi_header));
}

std::map<std::string, std::string> ServerHandler::getCgiHeader(const std::string& cgi_header_str)
{
    std::vector<std::string> arr = ft::splitString(cgi_header_str, "\r\n");
    std::map<std::string, std::string> cgi_header;
    for (std::vector<std::string>::iterator it = arr.begin(); it != arr.end(); it++)
    {
        size_t pos;
        std::string key;
        std::string value;
        if ((pos = (*it).find(':')) != std::string::npos)
        {
            key = (*it).substr(0, pos);
            value = (*it).substr(pos + 2, (*it).length() - pos - 1);
            cgi_header[key] = value;
        }
    }
    return (cgi_header);
}

int ServerHandler::getStautsCgi(const std::map<std::string, std::string>& cgi_header)
{
    int status;
    std::string status_str;
    std::vector<std::string> arr;
    if (cgi_header.find("Status") == cgi_header.end())
        return (-1);
    status_str = cgi_header.at("Status").substr(0, 3);
    if (status_str.length() != 3 || !ft::isNumbers(status_str))
    {
        Logger::writeErrorLog("Cgi Status is invaild");
        throw Error500Exceptnion();
    }
    status = ft::stoi(status_str);
    if (status < 100 || status >= 600)
    {
        Logger::writeErrorLog("Cgi Status is invaild");
        throw Error500Exceptnion();
    }
    return (status);
}

const char* ServerHandler::AutoIndexExceptnion::what() const throw() {
  return "Auto Index";
}
const char* ServerHandler::Error400Exceptnion::what() const throw() {
  return "Bad Request";
}
const char* ServerHandler::Error403Exceptnion::what() const throw() {
  return "Forbidden";
}
const char* ServerHandler::Error404Exceptnion::what() const throw() {
  return "Not Found";
}
const char* ServerHandler::Error405Exceptnion::what() const throw() {
  return "Method Not Allowed";
}
const char* ServerHandler::Error413Exceptnion::what() const throw() {
  return "Content Too Large";
}
const char* ServerHandler::Error414Exceptnion::what() const throw() {
  return "URI Too Long";
}
const char* ServerHandler::Error422Exceptnion::what() const throw() {
  return "Unprocessable Content";
}
const char* ServerHandler::Error500Exceptnion::what() const throw() {
  return "Internal Server Error";
}
const char* ServerHandler::Error503Exceptnion::what() const throw() {
  return "Service Unavailable";
}
