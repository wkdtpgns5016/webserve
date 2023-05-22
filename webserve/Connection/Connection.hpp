#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "../HttpMessage/HttpRequestMessage.hpp"
#include <iostream>

class Connection
{
    private:
    bool        _complete;
    bool        _is_empty_line;
    bool        _is_chunked;
    std::string _client_addr;
    std::string _message;
    
    void checkEmptyLine(std::string message);
    void checkChunk();
    void checkChunkComplete(std::string message);

    public:
    Connection();
    Connection(std::string client_addr);
    Connection(const Connection& connection);
    Connection& operator=(const Connection& connection);
    ~Connection();

    void appendMessage(std::string new_str);
    std::string getMessage() const;
    bool        checkMessage() const;
};

#endif