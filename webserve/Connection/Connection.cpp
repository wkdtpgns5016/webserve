#include "Connection.hpp"

Connection::Connection() : _complete(false), _is_empty_line(false), _is_chunked(false)
{

}

Connection::Connection(std::string clent_addr)
 : _complete(false), _is_empty_line(false), _is_chunked(false), _client_addr(clent_addr)
{

}

Connection::Connection(const Connection& connection)
{
    _complete = connection._complete;
    _message = connection._message;
    _client_addr = connection._client_addr;
}

Connection& Connection::operator=(const Connection& connection)
{
    _complete = connection._complete;
    _message = connection._message;
    _client_addr = connection._client_addr;
    return (*this);
}

Connection::~Connection()
{

}

void Connection::checkEmptyLine(std::string message)
{
    if (message.length() >= 4)
    {
        if (message.find("\r\n\r\n") != std::string::npos)
            _is_empty_line = true;
    }
    else
    {
        if (_message.find("\r\n\r\n") != std::string::npos)
            _is_empty_line = true;
    }
}

void Connection::checkChunk()
{
    if (_message.find("chunked") != std::string::npos)
    {
        _is_chunked = true;
    }
}

void Connection::checkChunkComplete(std::string message)
{
    if (message.length() >= 5)
    {
        if (message.find("\r\n0\r\n") != std::string::npos)
            _complete = true;
    }
    else
    {
        if (_message.find("\r\n0\r\n") != std::string::npos)
            _complete = true;
    }
}

void Connection::appendMessage(std::string new_str)
{
    _message += new_str;
    if (!_is_empty_line)
        checkEmptyLine(new_str);
    if (_is_empty_line) 
    {
        if (!_is_chunked)
            checkChunk();
        checkChunkComplete(new_str);
    }
}

std::string Connection::getMessage() const
{
    return (_message);
}

bool        Connection::checkMessage() const
{
    if (_is_chunked && _complete)
        return (true);
    else if (!_is_chunked && _is_empty_line)
        return (true);
    return (false);
}
