#include "Connection.hpp"

Connection::Connection()
{

}

Connection::Connection(int client_fd, const std::string& clent_addr)
 : _client_fd(client_fd), _client_addr(clent_addr), _current_connection_time(std::time(NULL)), _complete_respose(false), _start_read(false)
{
}

Connection::Connection(const Connection& connection)
{
    _client_fd = connection._client_fd;
    _client_addr = connection._client_addr;
    _message_parser = connection._message_parser;
    _current_connection_time = connection._current_connection_time;
    _complete_respose = connection._complete_respose;
    _start_read = connection._start_read;
}

Connection& Connection::operator=(const Connection& connection)
{
    _client_fd = connection._client_fd;
    _client_addr = connection._client_addr;
    _message_parser = connection._message_parser;
    _current_connection_time = connection._current_connection_time;
    _complete_respose = connection._complete_respose;
    _start_read = connection._start_read;
    return (*this);
}

Connection::~Connection()
{

}

bool Connection::receiveMessage(std::vector<ServerBlock *> configs)
{
    size_t buffer_size = 300000;
    char recv[buffer_size];
    size_t n;
    if (!_start_read)
    {
        //std::cout << std::clock() << "              start parsing request" << std::endl;
         _start_read = true;
    }
    n = read(_client_fd, recv, buffer_size);
    if (n < 0)
    {
        Logger::writeInfoLog(_client_fd, "Read error", true);
        return (false);
    }
    else if (n == 0)
    {
        Logger::writeInfoLog(_client_fd, "Close Connection client", false);
        return (false);
    }
    else
    {
        updateConnectionTime();
        parseHttpMessage(recv, n, configs);
    }
    return (true);
}

bool Connection::sendMessage()
{
    if (!checkResponse())
        return (true);

    size_t buffer_size = 300000;
    size_t len = std::strlen(_buffer.getBuffer());
    int n;
    if (len <= buffer_size)
        n = write(_client_fd, _buffer.getBuffer(), len);
    else
        n = write(_client_fd, _buffer.getBuffer(), buffer_size);
    
    if (n < 0)
    {
        Logger::writeInfoLog(_client_fd, "Write error", true);
        return (false);
    }
    else if (n == 0 || (size_t)n == len)
    {
        //std::cout << std::clock() << "              complete wrtie" << std::endl;
        //std::cout << std::clock() << "              end" << std::endl;
        clearConnection();
        Logger::writeLog(_client_addr, _request, _response);
        if (_response.getStartLine().getStatusCode() == 400)
        {
            Logger::writeInfoLog(_client_fd, "Close Connection client", false);
            return (false);
        }
    }
    else
    {
        updateConnectionTime();
        _buffer.cutBuffer(n);
    }
    return (true);
}

void Connection::parseHttpMessage(char* buffer, size_t len, std::vector<ServerBlock *> configs)
{
    ServerBlock* config = selectServerConfig(configs);
    try
    {
        _message_parser.appendMessage(buffer, len);
        if (checkMessage())
            makeResponse(config);
    }
    catch (const RequestMessageParser::InvalidRequestException& e)
    {
        GetHandler handler;
        _request = _message_parser.getRequestMessage();
        handler = GetHandler(config, _request);
        _response = handler.getErrorResponse(400);
        _buffer = Buffer(_response.getString());
        _complete_respose = true;
    }
}


ServerBlock* Connection::selectServerConfig(std::vector<ServerBlock *> configs)
{
    std::vector<ServerBlock *>::iterator it = configs.begin();

    if (_request.getHeaders().count("Host") < 0)
        return (*it);
    else
    {
        for (; it != configs.end(); it++)
        {
            if (_request.getHeaders().find("Host")->second == (*it)->getServerName())
                return (*it);
        }
    }
}

void Connection::makeResponse(ServerBlock *server_block)
{
    //std::cout << std::clock() << "              complete parsing reqeust " << std::endl;
    //std::cout << std::clock() << "              start parsing response" << std::endl;
    ServerController controller;
    _request = _message_parser.getRequestMessage();
    _response = controller.requestHandler(server_block, _request);
    //std::cout << std::clock() << "              complete parsing response" << std::endl;
    //std::cout << std::clock() << "              start write" << std::endl;
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
