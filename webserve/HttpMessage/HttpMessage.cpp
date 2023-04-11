#include "HttpMessage.hpp"

StartLine::StartLine(void)
{

}

StartLine::StartLine(std::string http_version) : _http_version(http_version)
{

}

StartLine::StartLine(const StartLine& start_line)
{
    if (this == &start_line)
        return ;
    _http_version = start_line.getHttpVersion();
    return ;
}

StartLine::~StartLine(void)
{

}

StartLine& StartLine::operator=(const StartLine& start_line)
{
    if (this == &start_line)
        return (*this);
    _http_version = start_line.getHttpVersion();
    return (*this);

}

std::string StartLine::getHttpVersion(void) const
{
    return (_http_version);
}

bool        checkHttpVersion(std::string http_version)
{
    return (true);
}

StatusLine::StatusLine(void) : StartLine()
{

}

StatusLine::StatusLine(std::string start_line)
{
    std::vector<std::string> arr;
    int status_code;

    arr = ft::splitString(start_line, " ");
    _http_version = arr[0];
    _status_code = std::atoi(arr[1].c_str());
    _status_message = arr[2];
}

StatusLine::StatusLine(const StatusLine& status_line)
{
    if (this == &status_line)
        return ;
    _http_version = status_line.getHttpVersion();
    _status_code = status_line.getStatusCode();
    _status_message = status_line.getStatusMessage();
    return ;
}

StatusLine::~StatusLine(void)
{

}

StatusLine& StatusLine::operator=(const StatusLine& status_line)
{
    if (this == &status_line)
        return (*this);
    _http_version = status_line.getHttpVersion();
    _status_code = status_line.getStatusCode();
    _status_message = status_line.getStatusMessage();
    return (*this);
}

int StatusLine::getStatusCode(void) const
{
    return (_status_code);
}

std::string StatusLine::getStatusMessage(void) const
{
    return (_status_message);
}

bool StatusLine::checkStatusCode(std::string status_code)
{
    return (true);
}

bool StatusLine::checkStatusMessage(std::string status_message)
{
    return (true);
}

bool    StatusLine::isVaild(std::vector<std::string> arr)
{
    if (arr.size() != 3)
        return (false);
    if (!::checkHttpVersion(arr[0]))
        return (false);
    if (!checkStatusCode(arr[1]))
        return (false);
    if (!checkStatusMessage(arr[2]))
        return (false);
    return (true);
}

std::string StatusLine::getString(void)
{
    std::stringstream ss;
    ss << _status_code;
    return (_http_version + " " + ss.str() + " " + _status_message);
}

RequestLine::RequestLine(void)
{

}

RequestLine::RequestLine(std::string start_line)
{
    std::vector<std::string> arr;
    int status_code;

    arr = ft::splitString(start_line, " ");
    _http_method = arr[0];
    _request_target = arr[1];
    _http_version = arr[2];
}

RequestLine::RequestLine(const RequestLine& request_line)
{
    if (this == &request_line)
        return ;
    _http_version = request_line.getHttpVersion();
    _http_method = request_line.getHttpMethod();
    _request_target = request_line.getRequestTarget();
    return ;
}

RequestLine::~RequestLine(void)
{

}

RequestLine& RequestLine::operator=(const RequestLine& request_line)
{
    if (this == &request_line)
        return (*this);
    _http_version = request_line.getHttpVersion();
    _http_method = request_line.getHttpMethod();
    _request_target = request_line.getRequestTarget();
    return (*this);
}

std::string RequestLine::getHttpMethod(void) const
{
    return (_http_method);
}

std::string RequestLine::getRequestTarget(void) const
{
    return (_request_target);
}

bool RequestLine::checkHttpMethod(std::string http_method)
{
    return (true);
}

bool RequestLine::checkRequestTarget(std::string request_target)
{
    return (true);
}

bool RequestLine::isVaild(std::vector<std::string> arr)
{
    if (arr.size() != 3)
        return (false);
    if (!checkHttpMethod(arr[0]))
        return (false);
    if (!checkRequestTarget(arr[1]))
        return (false);
    if (!::checkHttpVersion(arr[2]))
        return (false);
    return (true);
}

std::string RequestLine::getString(void)
{
    return (_http_method + " " + _request_target + " " + _http_version);
}

HttpMessage::HttpMessage(void)
{

}

bool HttpMessage::checkHeaders(std::vector<std::string> arr)
{
    return (true);
}

void HttpMessage::setHeaders(std::string header)
{
    std::vector<std::string> arr;
    std::string filed;
    std::string value;
    int pos;

    arr = ft::splitString(header, "\r\n");
    // header 유효성 검사
    for (std::vector<std::string>::iterator it = arr.begin(); it < arr.end(); it++)
    {
        pos = (*it).find(':');
        filed = (*it).substr(0, pos);
        value = (*it).substr(pos + 2, (*it).length() - pos - 1);
        _headers[filed] = value;
    }
}

HttpMessage::HttpMessage(std::string http_message)
{
    std::istringstream iss(http_message);
    std::string token;
    std::string s;

    std::getline(iss, token, '\n');
    while (std::getline(iss, token, '\n'))
    {
        s += token + "\n";
        if (token.compare("\r") == 0)
            break;
    }
    setHeaders(s);
    s.clear();
    while (std::getline(iss, token, '\n'))
        s += token + "\n";
    _message_body = s.substr(0, s.length() - 1);
}

HttpMessage::HttpMessage(const HttpMessage& http_message)
{
    if (this == &http_message)
        return ;
    _headers = http_message.getHeaders();
    _message_body = http_message.getMessageBody();
    return ;
}

HttpMessage::~HttpMessage(void)
{

}

HttpMessage& HttpMessage::operator=(const HttpMessage& http_message)
{
    if (this == &http_message)
        return (*this);
    _headers = http_message.getHeaders();
    _message_body = http_message.getMessageBody();
    return (*this);
}

std::map<std::string, std::string> HttpMessage::getHeaders(void) const
{
    return (_headers);
}

std::string HttpMessage::getMessageBody(void) const
{
    return (_message_body);
}
