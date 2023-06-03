#include "Connection.hpp"

Connection::Connection()
{

}

Connection::Connection(int client_fd, std::string clent_addr)
 : _client_fd(client_fd), _client_addr(clent_addr), _current_connection_time(std::time(NULL)), _complete_respose(false), _start_read(false)
{
    i = 0;
}

Connection::Connection(const Connection& connection)
{
    _client_fd = connection._client_fd;
    _client_addr = connection._client_addr;
    _message_parser = connection._message_parser;
    _current_connection_time = connection._current_connection_time;
    _complete_respose = connection._complete_respose;
    _start_read = connection._start_read;
    i = 0;
}

Connection& Connection::operator=(const Connection& connection)
{
    _client_fd = connection._client_fd;
    _client_addr = connection._client_addr;
    _message_parser = connection._message_parser;
    _current_connection_time = connection._current_connection_time;
    _complete_respose = connection._complete_respose;
    _start_read = connection._start_read;
    i = 0;
    return (*this);
}

Connection::~Connection()
{

}

bool Connection::receiveMessage()
{
    //std::vector<char> buffer;
    size_t buffer_size = 300000;
    char recv[buffer_size];
    size_t n;
    i++;
    if (!_start_read)
    {
        std::cout << std::clock() << "              start parsing request" << std::endl;
         _start_read = true;
    }
    n = read(_client_fd, recv, buffer_size);
    if (n < 0)
    {
        Logger::writeLog(_client_addr, _client_fd, "read error", 1);
        return (false);
    }
    else if (n == 0)
    {
        Logger::writeLog(_client_addr, _client_fd, "Close Connection client", 1);
        return (false);
    }
    else
    {
        updateConnectionTime();
        //buffer.insert(buffer.end(), recv, recv + n);
        //std::string recv_message(buffer.begin(), buffer.end());
        _message_parser.appendMessage(recv, n);
    }
    return (true);
}

bool Connection::sendMessage(ServerBlock *server_block)
{
    if (checkMessage())
    {
        if (!checkResponse())
            makeResponse(server_block);

        size_t buffer_size = 300000;
        size_t len = std::strlen(_buffer.getBuffer());
        int n;
        if (len <= buffer_size)
            n = write(_client_fd, _buffer.getBuffer(), len);
        else
            n = write(_client_fd, _buffer.getBuffer(), buffer_size);
        
        if (n < 0)
        {
            Logger::writeLog(_client_addr, _client_fd, "write error", 1);
            return (false);
        }
        else if (n == 0 || (size_t)n == len)
        {
            std::cout << std::clock() << "              complete wrtie" << std::endl;
            std::cout << std::clock() << "              end" << std::endl;
            clearConnection();
            Logger::writeLog(_client_addr, _request, _response, 1);
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
    std::cout << std::clock() << "              complete parsing reqeust " << i << std::endl;
    std::cout << std::clock() << "              start parsing response" << std::endl;
    ServerController controller;
    _request = _message_parser.getRequestMessage();
    _response = controller.requestHandler(server_block, _request);
    std::cout << std::clock() << "              complete parsing response" << std::endl;
    std::cout << std::clock() << "              start write" << std::endl;
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
    _start_read = false;
}

bool Connection::checkMessage() { return (_message_parser.checkMessage()); }
bool Connection::checkResponse() { return (_complete_respose); }
std::string Connection::getClinetAddr() const { return (_client_addr); }
int Connection::getClinetFd() const { return (_client_fd); }
time_t Connection::getCurrentConnectionTime() const { return (_current_connection_time); }
