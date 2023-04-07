#ifndef HTTP_MESSAGE_HPP
#define HTTP_MESSAGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include "../lib/ft/ft.hpp"

class StartLine
{
protected:
    std::string _http_version;

public:
    StartLine(void);
    StartLine(std::string http_version);
    StartLine(const StartLine& start_line);
    ~StartLine(void);
    StartLine& operator=(const StartLine& start_line);

    std::string         getHttpVersion(void) const;
    virtual bool        isVaild(void) = 0;
    virtual std::string getString(void) = 0;
};

class StatusLine : public StartLine
{
private:
    int         _status_code;
    std::string _status_message;

public:
    StatusLine(void);
    StatusLine(std::string start_line);
    StatusLine(const StatusLine& status_line);
    ~StatusLine(void);
    StatusLine& operator=(const StatusLine& status_line);

    int         getStatusCode(void) const;
    std::string getStatusMessage(void) const;
    bool        isVaild(void);
    std::string getString(void);
};

class RequestLine : public StartLine
{
private:
    std::string _http_method;
    std::string _request_target;

public:
    RequestLine(void);
    RequestLine(std::string start_line);
    RequestLine(const RequestLine& request_line);
    ~RequestLine(void);
    RequestLine& operator=(const RequestLine& request_line);

    std::string getHttpMethod(void) const;
    std::string getRequestTarget(void) const;
    bool        isVaild(void);
    std::string getString(void);
};

class HttpMessage
{
protected:
    std::map<std::string, std::string>  _headers;
    std::string                         _message_body;

private:
    void                                setHeaders(std::string header);

public:
    HttpMessage(void);
    HttpMessage(std::string http_message);
    HttpMessage(const HttpMessage& http_message);
    ~HttpMessage(void);
    HttpMessage& operator=(const HttpMessage& http_message);

    std::map<std::string, std::string>  getHeaders(void) const;
    std::string                         getMessageBody(void) const;
    virtual bool                        isVaild(void) = 0;
    virtual std::string                 getString(void) = 0;
};

#endif