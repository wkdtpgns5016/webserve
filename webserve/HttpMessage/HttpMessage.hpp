#ifndef HTTP_MESSAGE_HPP
#define HTTP_MESSAGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <exception>
#include "../lib/ft/ft.hpp"

class StartLine
{
protected:
    std::string _http_version;

    bool        checkHttpVersion(std::string http_version);
public:
    StartLine(void);
    StartLine(const std::string& http_version);
    StartLine(const StartLine& start_line);
    ~StartLine(void);
    StartLine& operator=(const StartLine& start_line);

    std::string         getHttpVersion(void) const;
    virtual bool        isVaild(std::vector<std::string> arr) = 0;
    virtual std::string getString(void) = 0;
};

class StatusLine : public StartLine
{
private:
    int         _status_code;
    std::string _status_message;

    bool        checkStatusCode(const std::string& status_code);
    bool        checkStatusMessage(const std::string& status_message);
public:
    StatusLine(void);
    StatusLine(const std::string& start_line);
    StatusLine(const std::string& http_version, int status_code, const std::string& status_message);
    StatusLine(const StatusLine& status_line);
    ~StatusLine(void);
    StatusLine& operator=(const StatusLine& status_line);

    int         getStatusCode(void) const;
    std::string getStatusMessage(void) const;
    bool        isVaild(std::vector<std::string> arr);
    std::string getString(void);
};

class RequestLine : public StartLine
{
private:
    std::string _http_method;
    std::string _request_target;

    bool        checkHttpMethod(const std::string& http_method);
    bool        checkRequestTarget(const std::string& request_target);

public:
    RequestLine(void);
    RequestLine(const std::string& start_line);
    RequestLine(const std::string& http_method, const std::string& request_target, const std::string& http_version);
    RequestLine(const RequestLine& request_line);
    ~RequestLine(void);
    RequestLine& operator=(const RequestLine& request_line);

    std::string getHttpMethod(void) const;
    std::string getRequestTarget(void) const;
    bool        isVaild(std::vector<std::string> arr);
    std::string getString(void);
};

class HttpMessage
{
protected:
    
    std::map<std::string, std::string>  _headers;
    std::string                         _message_body;
    std::string                         _chunked_message_body;
    size_t                              _message_size;
    size_t                              _chunked_size;

private:
    void                                setHeaders(const std::string& header);
    bool                                checkHeaders(std::vector<std::string> arr);
    void                                setMessageBody(const std::string& message_body);
    std::string                         mergeChunkedMessage(const std::string& chunk);

public:
    HttpMessage(void);
    HttpMessage(const std::string& http_message);
    HttpMessage(std::map<std::string, std::string>  headers, const std::string& message_body);
    HttpMessage(const HttpMessage& http_message);
    ~HttpMessage(void);
    HttpMessage& operator=(const HttpMessage& http_message);

    std::map<std::string, std::string>  getHeaders(void) const;
    std::string                         getMessageBody(void);
    virtual std::string                 getString(void) = 0;
    virtual bool                        isVaild(void) = 0;
    size_t                              getMessageSize(void) const;
    bool                                checkChunked(void) const;
    void                                changeChunkedMessage(size_t encoding_size);
};

#endif