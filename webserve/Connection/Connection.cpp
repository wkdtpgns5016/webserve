#include "Connection.hpp"

Connection::Connection()
{

}

Connection::Connection(int client_fd, std::string clent_addr)
 : _client_fd(client_fd), _client_addr(clent_addr)
{

}

Connection::Connection(const Connection& connection)
{
    _client_fd = connection._client_fd;
    _client_addr = connection._client_addr;
    _message_parser = connection._message_parser;
}

Connection& Connection::operator=(const Connection& connection)
{
    _client_fd = connection._client_fd;
    _client_addr = connection._client_addr;
    _message_parser = connection._message_parser;
    return (*this);
}

Connection::~Connection()
{

}

void Connection::receiveMessage()
{
    std::vector<unsigned char> _buffer;
    unsigned char recv[1024] = { 0, };
    size_t n;

    n = read(_client_fd, recv, 1024);
    _buffer.insert(_buffer.end(), recv, recv + n);
    std::string recv_message(_buffer.begin(), _buffer.end());
    
    _message_parser.appendMessage(recv_message, recv_message.length());
}

bool Connection::sendMessage(ServerBlock *server_block)
{
    if (checkMessage())
    {
        ServerController controller;
        HttpRequestMessage request_message = _message_parser.getRequestMessage();
        HttpResponseMessage message = controller.requestHandler(server_block, request_message);
        std::string m = message.getString();
        const char* msg = m.c_str();
        size_t i = 0;
        size_t n;
        size_t len = message.getString().size();
        if (len <= 1023)
            write(_client_fd, message.getString().c_str(), len);
        else
        {
            while (1)
            {
                n = write(_client_fd, msg + i, 1023);
                i += n;
                if (i >= len)
                    break ;
            }
        }
        //write(_client_fd, message.getString().c_str(), message.getString().size());
        CommonLogFormat log = CommonLogFormat(_client_addr, request_message, message);
        log.wirteLogMessage(1);
        return (true);
    }
    return (false);
}

bool Connection::checkMessage() { return (_message_parser.checkMessage()); }
std::string Connection::getClinetAddr() const { return (_client_addr); }
