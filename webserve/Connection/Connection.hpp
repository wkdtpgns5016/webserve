#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "../HttpMessage/HttpRequestMessage.hpp"
#include <iostream>

class Connection
{
    private:
    bool        _is_chunked;
    bool        _complete_start_line;
    bool        _complete_header;
    bool        _complete_body;

    std::string _client_addr;
    std::string _message;

    std::string _start_line_str;
    std::string _header_str;
    std::string _message_body_str;

    RequestLine _start_line;
    std::map<std::string, std::string> _header;

    HttpRequestMessage _request_message;
    
    void checkChunk();
    void checkChunkComplete(std::string message, size_t len);
    bool findZero(std::vector<std::string> arr);

    void initStartLine(std::string message);
    void initHeader(std::string message);
    void initBody(std::string message, size_t len);

    void setHeader(std::string message);

    public:
    Connection();
    Connection(std::string client_addr);
    Connection(const Connection& connection);
    Connection& operator=(const Connection& connection);
    ~Connection();

    void appendMessage(std::string new_str, size_t len);
    std::string getMessage() const;
    HttpRequestMessage getRequestMessage() const;
    std::string getClinetAddr() const;
    bool        checkMessage() const;
};

#endif