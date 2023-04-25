#ifndef COMMONLOGFORMAT_HPP
#define COMMONLOGFORMAT_HPP

#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"
#include "../lib/ft/ft.hpp"
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <map>

class CommonLogFormat
{
    private:
    std::string _remote_host;
    std::string _user_name;
    std::string _auth_user_name;
    std::string _time_stamp;
    RequestLine _request_line;
    int         _status_code;
    std::string _response_size;
    
    public:
    CommonLogFormat();
    CommonLogFormat(HttpRequestMessage request_message, HttpResponseMessage response_message);
    CommonLogFormat(const CommonLogFormat& log_format);
    ~CommonLogFormat();
    CommonLogFormat& operator=(const CommonLogFormat& log_format);
    
    void initTimeStamp(void);
    std::string getString(void);
    void wirteLogMessage(int fd);

    std::string getRemoteHost(void) const;
    std::string getUserName(void) const;
    std::string getAuthUserName(void) const;
    std::string getTimeStamp(void) const;
    RequestLine getRequestLine(void) const;
    int getStatusCode(void) const;
    std::string getResponseSize(void) const;
};

#endif