#include "HttpRequestMessage.hpp"

HttpRequestMessage::HttpRequestMessage(void) : HttpMessage()
{

}

HttpRequestMessage::HttpRequestMessage(std::string http_message) : HttpMessage(http_message)
{
    std::string start_line;
    std::vector<std::string> arr;
    int pos;

    pos = http_message.find("\r\n");
    start_line = http_message.substr(0, pos);
    _start_line = RequestLine(start_line);
    return ;
}

HttpRequestMessage::HttpRequestMessage(RequestLine                         start_line,
                                       std::map<std::string, std::string>  headers, 
                                       std::string                         message_body)
: HttpMessage(headers, message_body), _start_line(start_line)
{

}

HttpRequestMessage::HttpRequestMessage(const HttpRequestMessage& http_message) : HttpMessage()
{
    if (this == &http_message)
        return ;
    _start_line = http_message.getStartLine();
    _headers = http_message.getHeaders();
    _message_body = http_message.getMessageBody();
    return ;
}

HttpRequestMessage::~HttpRequestMessage(void)
{

}

HttpRequestMessage& HttpRequestMessage::operator=(const HttpRequestMessage& http_message)
{
    if (this == &http_message)
        return (*this);
    _start_line = http_message.getStartLine();
    _headers = http_message.getHeaders();
    _message_body = http_message.getMessageBody();
    return (*this);
}


RequestLine HttpRequestMessage::getStartLine(void) const
{
    return (_start_line);
}

bool HttpRequestMessage::isVaild(void)
{
    return (true);
}

std::string HttpRequestMessage::getString(void)
{
    std::string str;

    str = _start_line.getString() + "\r\n";
    for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); it++)
    {
        str += (*it).first + ": " + (*it).second + "\r\n";
    }
    str += "\r\n";
    str += _message_body;
    return (str);
}
