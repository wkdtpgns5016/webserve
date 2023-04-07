#ifndef HTTP_RESPONSE_MESSAGE_HPP
#define HTTP_RESPONSE_MESSAGE_HPP

#include "HttpMessage.hpp"

class HttpResponseMessage : public HttpMessage
{

private:
    StatusLine _status_line;

public:
    HttpResponseMessage(void);
    HttpResponseMessage(std::string http_message);
    HttpResponseMessage(const HttpResponseMessage& http_meesage);
    ~HttpResponseMessage(void);
    HttpResponseMessage& operator=(const HttpResponseMessage& http_meesage);

    StatusLine getStartLine(void) const;
    bool isVaild(void);
    std::string getString(void);
};

#endif