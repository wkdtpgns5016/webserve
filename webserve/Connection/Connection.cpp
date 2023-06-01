#include "Connection.hpp"

Connection::Connection()
{

}

Connection::Connection(int client_fd, std::string clent_addr)
 : _client_fd(client_fd), _client_addr(clent_addr), _current_connection_time(std::time(NULL)), _complete_respose(false)
{

}

Connection::Connection(const Connection& connection)
{
    _client_fd = connection._client_fd;
    _client_addr = connection._client_addr;
    _message_parser = connection._message_parser;
    _current_connection_time = connection._current_connection_time;
    _complete_respose = connection._complete_respose;
}

Connection& Connection::operator=(const Connection& connection)
{
    _client_fd = connection._client_fd;
    _client_addr = connection._client_addr;
    _message_parser = connection._message_parser;
    _current_connection_time = connection._current_connection_time;
    _complete_respose = connection._complete_respose;
    return (*this);
}

Connection::~Connection()
{

}

bool Connection::receiveMessage()
{
    std::vector<unsigned char> _buffer;
    unsigned char recv[1024] = { 0, };
    size_t n;

    n = read(_client_fd, recv, 1024);
    if (n < 0)
    {
        std::cout << "n < 0" << std::endl;
        return (false);
    }
    else if (n == 0)
    {
        std::cout << "n == 0" << std::endl;
        return (false);
    }
    else
    {
        updateConnectionTime();
        _buffer.insert(_buffer.end(), recv, recv + n);
        std::string recv_message(_buffer.begin(), _buffer.end());
        _message_parser.appendMessage(recv_message, recv_message.length());
    }
    return (true);
}

bool Connection::sendMessage(ServerBlock *server_block)
{
    if (checkMessage())
    {
        if (!checkResponse())
            makeResponse(server_block);

        size_t buffer_size = 40000;
        size_t len = std::strlen(_buffer.getBuffer());
        int n;
        if (len <= buffer_size)
            n = write(_client_fd, _buffer.getBuffer(), len);
        else
            n = write(_client_fd, _buffer.getBuffer(), buffer_size);
        
        if (n < 0)
            return (false);
        else if (n == 0 || (size_t)n == len)
        {
            clearConnection();
            CommonLogFormat log = CommonLogFormat(_client_addr, _request, _response);
            log.wirteLogMessage(1);
        }
        else
        {
            updateConnectionTime();
            _buffer.cutBuffer(n);
        }
    }
    return (true);
}

void Connection::makeResponse(ServerBlock *server_block)
{
    ServerController controller;
    _request = _message_parser.getRequestMessage();
    _response = controller.requestHandler(server_block, _request);

    _buffer = Buffer(_response.getString());
    _complete_respose = true;
}

void Connection::updateConnectionTime()
{
    _current_connection_time = std::time(NULL);
}

void Connection::clearConnection()
{
    _message_parser = RequestMessageParser();
    _buffer.clearBuffer();
    _complete_respose = false;
}

bool Connection::checkMessage() { return (_message_parser.checkMessage()); }
bool Connection::checkResponse() { return (_complete_respose); }
std::string Connection::getClinetAddr() const { return (_client_addr); }
time_t Connection::getCurrentConnectionTime() const { return (_current_connection_time); }
