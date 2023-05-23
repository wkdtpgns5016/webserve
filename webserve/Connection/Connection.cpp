#include "Connection.hpp"

Connection::Connection()
 : _is_chunked(false), _complete_start_line(false), _complete_header(false), _complete_body(false)
{

}

Connection::Connection(std::string clent_addr)
 : _is_chunked(false), _complete_start_line(false), _complete_header(false), _complete_body(false), _client_addr(clent_addr)
{

}

Connection::Connection(const Connection& connection)
{
    _is_chunked = connection._is_chunked;
    _complete_start_line = connection._complete_start_line;
    _complete_header = connection._complete_header;
    _complete_body = connection._complete_body;
    _message = connection._message;
    _client_addr = connection._client_addr;
}

Connection& Connection::operator=(const Connection& connection)
{
    _is_chunked = connection._is_chunked;
    _complete_start_line = connection._complete_start_line;
    _complete_header = connection._complete_header;
    _complete_body = connection._complete_body;
    _message = connection._message;
    _client_addr = connection._client_addr;
    return (*this);
}

Connection::~Connection()
{

}

void Connection::checkChunk()
{
    if (_header.count("Transfer-Encoding") > 0)
    {
        if (_header["Transfer-Encoding"] == "chunked")
        {
            _is_chunked = true;
        }
    }
}

void Connection::checkChunkComplete(std::string message, size_t len)
{
    // trailer 헤더가 있을 경우
    std::string trailer;
    std::vector<std::string> line;

    if (_header.count("Trailer") > 0)
    {
        trailer = _header["Trailer"];

    }
    else
    {
        if (len >= 5)
            line = ft::splitString(message, "\r\n");
        else
            line = ft::splitString(_message_body_str, "\r\n");
        findZero(line);
    }

    // if (len >= 5)
    // {
    //     if (message.find("0\r\n\r\n") != std::string::npos)
    //         _complete_body = true;
    // }
    // else
    // {
    //     if (_message_body_str.find("0\r\n\r\n") != std::string::npos)
    //         _complete_body = true;
    // }
}

bool Connection::findZero(std::vector<std::string> arr)
{
    
}

void Connection::initStartLine(std::string message)
{
    size_t pos;
    std::string prev;
    std::string next;

    _start_line_str += message;
    if ((pos = _start_line_str.find("\r\n")) != std::string::npos)
    {
        prev = _start_line_str.substr(0, pos);
        if (prev.length() < _start_line_str.length() - 2)
            next = _start_line_str.substr(pos + 2);
        _start_line_str = prev;
        _start_line = RequestLine(_start_line_str);
        _complete_start_line = true;
        initHeader(next);
    }
}

void Connection::initHeader(std::string message)
{
    size_t pos;
    std::string prev;
    std::string next;

    _header_str += message;
    if ((pos = _header_str.find("\r\n\r\n")) != std::string::npos)
    {
        prev = _header_str.substr(0, pos + 4);
        if (prev.length() < _header_str.length())
            next = _header_str.substr(pos + 4);
        _header_str = prev;
        setHeader(_header_str);
        _complete_header = true;
        checkChunk();
        initBody(next, next.length());
    }
}

void Connection::initBody(std::string message, size_t len)
{
    _message_body_str += message;
    if (_is_chunked)
        checkChunkComplete(message, len);
    else
    {
        if (_header.count("Content-Length") > 0)
        {
            size_t content_size = ft::stoi(_header["Content-Length"]);
            if (_message_body_str.length() == content_size)
                _complete_body = true;
        }
        else
            _complete_body = true;
    }
}

void Connection::setHeader(std::string message)
{
    std::vector<std::string> arr;
    std::string filed;
    std::string value;
    int pos;

    arr = ft::splitString(message, "\r\n");
    for (std::vector<std::string>::iterator it = arr.begin(); it < arr.end(); it++)
    {
        pos = (*it).find(':');
        filed = (*it).substr(0, pos);
        value = (*it).substr(pos + 2, (*it).length() - pos - 1);
        _header[filed] = value;
    }
}

void Connection::appendMessage(std::string new_str, size_t len)
{
    if (!_complete_start_line)
        initStartLine(new_str);
    else if (!_complete_header)
        initHeader(new_str);
    else if (!_complete_body)
        initBody(new_str, len);
    if (_complete_start_line && _complete_header && _complete_body)
        _request_message = HttpRequestMessage(_start_line, _header, _message_body_str);
}

std::string Connection::getMessage() const
{
    return (_message);
}

std::string Connection::getClinetAddr() const
{
    return (_client_addr);
}

HttpRequestMessage Connection::getRequestMessage() const
{
    return (_request_message);
}

bool        Connection::checkMessage() const
{
    if (_complete_start_line && _complete_header && _complete_body)
        return (true);
    return (false);
}