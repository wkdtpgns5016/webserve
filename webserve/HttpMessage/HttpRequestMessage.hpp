#ifndef HTTP_REQUEST_MESSAGE_HPP
#define HTTP_REQUEST_MESSAGE_HPP

#include "HttpMessage.hpp"

class HttpRequestMessage : public HttpMessage
{
private:
    RequestLine _start_line;

public:
    HttpRequestMessage(void);
    HttpRequestMessage(std::string http_message);
    HttpRequestMessage(const HttpRequestMessage& http_meesage);
    ~HttpRequestMessage(void);
    HttpRequestMessage& operator=(const HttpRequestMessage& http_meesage);

    RequestLine getStartLine(void) const;
    bool isVaild(void);
    std::string getString(void);

};

#endif