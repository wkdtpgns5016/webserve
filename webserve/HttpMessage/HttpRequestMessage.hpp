#ifndef HTTP_REQUEST_MESSAGE_HPP
#define HTTP_REQUEST_MESSAGE_HPP

#include "HttpMessage.hpp"
#include <unistd.h>

class HttpRequestMessage : public HttpMessage
{
private:
    RequestLine _start_line;

public:
    HttpRequestMessage(void);
    HttpRequestMessage(const std::string& http_message);
    HttpRequestMessage(const RequestLine&                   start_line,
                        std::map<std::string, std::string>  headers, 
                        const std::string&                  message_body);
    HttpRequestMessage(const HttpRequestMessage& http_meesage);
    ~HttpRequestMessage(void);
    HttpRequestMessage& operator=(const HttpRequestMessage& http_meesage);

    RequestLine getStartLine(void) const;
    void setStartLine(const RequestLine& start_line);
    bool isVaild(void);
    std::string getString(void);

    std::string getReqeustTarget() const;
    std::string getHttpVersion() const;
    std::string getHttpMethod() const;
    std::string getQueryString() const;

    std::string getPathInfo() const;
    std::string getPathTranslate() const;

};

#endif