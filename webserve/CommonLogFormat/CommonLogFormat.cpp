#include "CommonLogFormat.hpp"

CommonLogFormat::CommonLogFormat()
 : _remote_host("127.0.0.1"), _user_name("-"), _auth_user_name("-"), _time_stamp("-"), 
   _request_line(RequestLine()), _status_code(0), _response_size(0)
{
    initTimeStamp();
}

CommonLogFormat::CommonLogFormat(HttpRequestMessage request_message, HttpResponseMessage response_message)
{
    initTimeStamp();
    _remote_host = "127.0.0.1";
    _user_name = "-";
    _auth_user_name = "-";
    _request_line = request_message.getStartLine();
    _status_code = response_message.getStartLine().getStatusCode();
    if (response_message.getMessageBody().length() == 0)
        _response_size = "-";
    _response_size = ft::itos(response_message.getMessageBody().length());
}

CommonLogFormat::CommonLogFormat(const CommonLogFormat& log_format)
{
    if (this == &log_format)
        return ;
    _remote_host = log_format._remote_host;
    _user_name = log_format._user_name;
    _auth_user_name = log_format._auth_user_name;
    _time_stamp = log_format._time_stamp;
    _request_line = log_format._request_line;
    _status_code = log_format._status_code;
    _response_size = log_format._response_size;
}

CommonLogFormat::~CommonLogFormat()
{

}

CommonLogFormat& CommonLogFormat::operator=(const CommonLogFormat& log_format)
{

    if (this == &log_format)
        return (*this);
    _remote_host = log_format._remote_host;
    _user_name = log_format._user_name;
    _auth_user_name = log_format._auth_user_name;
    _time_stamp = log_format._time_stamp;
    _request_line = log_format._request_line;
    _status_code = log_format._status_code;
    _response_size = log_format._response_size;
    return (*this);
}

void CommonLogFormat::initTimeStamp(void)
{
    time_t timer;
    std::string t;
    std::vector<std::string> arr;

    timer = time(NULL);
    //timer += 3600 * 9;
    t = std::string(std::ctime(&timer));
    arr = ft::splitString(t, " ");
    _time_stamp = "[" + arr[2] + "/"
                + arr[1] + "/"
                + arr[4].substr(0, arr[4].length() - 1) + ":"
                + arr[3] + " +0900]";
}
    
std::string CommonLogFormat::getString(void)
{
    std::string str;

    str = _remote_host + " "
        + _user_name + " "
        + _auth_user_name + " "
        + _time_stamp + " "
        + _request_line.getString() + " "
        + ft::itos(_status_code) + " "
        + _response_size + "\n";
    return (str);
}

void CommonLogFormat::wirteLogMessage(int fd)
{
    std::string log = getString();
    write(fd, log.c_str(), log.length());
}


std::string CommonLogFormat::getRemoteHost(void) const
{
    return (_remote_host);
}

std::string CommonLogFormat::getUserName(void) const
{
    return (_user_name);
}

std::string CommonLogFormat::getAuthUserName(void) const
{
    return (_auth_user_name);
}

std::string CommonLogFormat::getTimeStamp(void) const
{
    return (_time_stamp);
}

RequestLine CommonLogFormat::getRequestLine(void) const
{
    return (_request_line);
}

int CommonLogFormat::getStatusCode(void) const
{
    return (_status_code);
}

std::string CommonLogFormat::getResponseSize(void) const
{
    return (_response_size);
}
