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
    _b_config = location_block;
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

std::map<std::string, std::string> ServerHandler::setHeader(int status_code, std::string message_body, std::map<std::string, std::string> cgi_header)
{
    std::map<std::string, std::string> headers;
    std::vector<std::string> t = ft::getTime(time(NULL));

    headers["Server"] = "webserv";
    headers["Date"] = t[0] + ", " + t[2] + " " + t[1] + " " + t[4] + " " + t[3] + " GMT";
    if (cgi_header.find("Content-Type") != cgi_header.end())
        headers["Content-Type"] = cgi_header["Content-Type"];
    else
        headers["Content-Type"] = "text/html";
    headers["Content-Length"] = ft::itos(message_body.size());
    //headers["Connection"] = "close";
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

HttpResponseMessage ServerHandler::getResponseMessage(int status_code, std::string message_body, std::map <std::string, std::string> cgi_header)
{
    std::vector<std::string> arr;
    StatusLine start_line = StatusLine(_request_message.getHttpVersion(), status_code, _status[status_code]);
    std::map<std::string, std::string> headers = setHeader(status_code, message_body, cgi_header);
    HttpResponseMessage response_message = HttpResponseMessage(start_line, headers, message_body);
    return (response_message);
}

int ServerHandler::checkFile(std::string request_target)
{
    int len = request_target.length();
    if (len < 4)
        return (-1);
    if (request_target.substr(len - 3, 3).compare("php") == 0)
        return (1);
    else if (request_target.substr(len - 3, 3).compare("cgi") == 0)
        return (2);
    else if (request_target.substr(len - 2, 2).compare("pl") == 0)
        return (3);
    else if (request_target.substr(len - 2, 2).compare("py") == 0)
        return (4);
    else if (request_target.substr(len - 2, 2).compare("sh") == 0)
        return (5);
    else if (request_target.substr(len - 3, 3).compare("bla") == 0)
        return (6);
    else
        return (-1);
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
    LocationBlock* temp;
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
    {
        return (temp);
    }
    return (location);
}

std::string ServerHandler::cleanUrl(std::string url, bool request_target)
{
    std::vector<std::string> url_arr = ft::splitString(url, "/");
    std::vector<std::string>::iterator it = url_arr.begin();
    std::string new_url;

    if (url.compare("/") == 0)
        return (url);
    for (; it != url_arr.end(); it++)
    {
        new_url = new_url + "/" + *it;
    }
    if (url.back() == '/' && request_target)
        new_url += "/";
    return (new_url);
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
    std::string message_body;
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


std::string ServerHandler::tryFiles(std::vector<std::string> try_files)
{
    std::vector<std::string>::iterator it = try_files.begin();
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

std::string ServerHandler::findPath(std::string request_target)
{
    std::string root = _config.getRoot();
    std::string index = _config.getIndex();

    // 요청 url
    std::string path = root + request_target;

    // 인덱싱 url
    std::vector<std::string> index_path = getIndexPath(path, index);

    std::string directory = path;
    if (directory.back() != '/')
        directory = path + "/";
    if (access(path.c_str(), F_OK) == -1)
    {
        // try_files
        std::vector<std::string> try_files = _config.getTryFiles();
        if (try_files.empty())
            throw Error404Exceptnion(); // 파일이 없을 경우
        else
            return (tryFiles(try_files));
    }
    else if (access(directory.c_str(), F_OK) != -1)
    {
        std::vector<std::string>::iterator it = index_path.begin();
        for (; it != index_path.end(); it++)
        {
            if (access((*it).c_str(), R_OK) == 0)      // 읽기 권한 있을 경우
                return (*it);
            else if (access((*it).c_str(), F_OK) == 0) // 권한이 없을 경우
                throw Error500Exceptnion();
        }
    }
    return(path);
}

void ServerHandler::checkHttpVersion(RequestLine start_line)
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
    if (arr[0].compare("HTTP") != 0)
        throw Error400Exceptnion();
    if (arr[1].compare("1.1") != 0)
        throw Error400Exceptnion();
}

void ServerHandler::checkMessageSize(void)
{
    size_t message_size = _request_message.getMessageSize();
    size_t client_max_body_size = _config.getClientMaxBodySize();
    
    if (message_size > client_max_body_size)
        throw Error413Exceptnion();
}

void ServerHandler::checkHttpMessage(void)
{
    // check start line
    RequestLine start_line = _request_message.getStartLine();
    checkAllowMethod(start_line.getHttpMethod());
    checkHttpVersion(start_line);

    // check message size
    checkMessageSize();
}

std::string ServerHandler::executeCgi(std::string file_path)
{
    CGI cgi(_b_config, _request_message);
    std::string script_name;
    std::string result;

    int flag = checkFile(file_path);

    switch (flag)
    {
    case 1:
        script_name = "/usr/bin/php " + file_path;
        break;
    case 2:
        script_name = "." + file_path;
        break;
    case 3:
        script_name = "/usr/bin/perl " + file_path;
        break;
    case 4:
        script_name = "/usr/bin/python " + file_path;
        break;
    case 5:
        script_name = "/bin/sh " + file_path;
        break;
    case 6:
        script_name = "./cgi_tester " + _request_message.getHttpMethod();
        break;
    default:
        script_name = "./" + file_path;
        break;
    }
    result = cgi.excute(script_name);
    return (result);
}

std::map<std::string, std::string> ServerHandler::getCgiHeader(std::vector<std::string> arr)
{
    std::map<std::string, std::string> cgi_header;
    for (std::vector<std::string>::iterator it = arr.begin(); it != arr.end() - 1; it++)
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

int ServerHandler::getStautsCgi(std::map<std::string, std::string> cgi_header)
{
    int status;
    std::vector<std::string> arr;
    if (cgi_header.find("Status") == cgi_header.end())
        return (-1);
    arr = ft::splitString(cgi_header["Status"], " ");
    if (arr.size() != 2)
        throw Error500Exceptnion();
    if (arr[0].length() != 3 || !ft::isNumbers(arr[0]))
        throw Error500Exceptnion();
    status = ft::stoi(arr[0]);
    if (status < 100 || status >= 600)
        throw Error500Exceptnion();
    return (status);
}

const char* ServerHandler::AutoIndexExceptnion::what() const throw() {
  return "Auto Index";
}
const char* ServerHandler::Error400Exceptnion::what() const throw() {
  return "Bad Request";
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
const char* ServerHandler::Error500Exceptnion::what() const throw() {
  return "Internal Server Error";
}
const char* ServerHandler::Error503Exceptnion::what() const throw() {
  return "Service Unavailable";
}
