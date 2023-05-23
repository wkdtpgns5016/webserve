#include "HttpResponseMessage.hpp"

HttpResponseMessage::HttpResponseMessage(void) : HttpMessage()
{

}

HttpResponseMessage::HttpResponseMessage(std::string http_message) : HttpMessage(http_message)
{
    std::string start_line;
    std::vector<std::string> arr;
    int pos;

    pos = http_message.find("\r\n");
    start_line = http_message.substr(0, pos);
    _start_line = StatusLine(start_line);
    return ;
}

HttpResponseMessage::HttpResponseMessage(const StatusLine&                   start_line,
                                         std::map<std::string, std::string>  headers, 
                                         const std::string&                  message_body)
: HttpMessage(headers, message_body), _start_line(start_line)
{

}

HttpResponseMessage::HttpResponseMessage(const HttpResponseMessage& http_meesage)
{
    if (this == &http_meesage)
        return ;
    _start_line = http_meesage.getStartLine();
    _headers = http_meesage.getHeaders();
    _message_body = http_meesage.getMessageBody();
    return ;
}

HttpResponseMessage::~HttpResponseMessage(void)
{

}

HttpResponseMessage& HttpResponseMessage::operator=(const HttpResponseMessage& http_meesage)
{
    if (this == &http_meesage)
        return (*this);
    _start_line = http_meesage.getStartLine();
    _headers = http_meesage.getHeaders();
    _message_body = http_meesage.getMessageBody();
    return (*this);
}

StatusLine HttpResponseMessage::getStartLine(void) const
{
    return (_start_line);
}

bool HttpResponseMessage::isVaild(void)
{
    return (true);
}

std::string HttpResponseMessage::getString(void)
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
