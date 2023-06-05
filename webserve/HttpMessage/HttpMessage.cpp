#include "HttpMessage.hpp"

StartLine::StartLine(void)
{

}

StartLine::StartLine(const std::string& http_version) : _http_version(http_version)
{

}

StartLine::StartLine(const StartLine& start_line)
{
    if (this == &start_line)
        return ;
    _http_version = start_line.getHttpVersion();
    return ;
}

StartLine::~StartLine(void)
{

}

StartLine& StartLine::operator=(const StartLine& start_line)
{
    if (this == &start_line)
        return (*this);
    _http_version = start_line.getHttpVersion();
    return (*this);

}

std::string StartLine::getHttpVersion(void) const
{
    return (_http_version);
}

bool        checkHttpVersion(std::string http_version)
{
    (void)http_version;
    return (true);
}

StatusLine::StatusLine(void) : StartLine()
{

}

StatusLine::StatusLine(const std::string& start_line)
{
    std::vector<std::string> arr;

    arr = ft::splitString(start_line, " ");
    _http_version = arr[0];
    _status_code = std::atoi(arr[1].c_str());
    _status_message = arr[2];
}

StatusLine::StatusLine(const std::string& start_line, int status_code, const std::string& status_message)
: StartLine(start_line), _status_code(status_code), _status_message(status_message)
{

}

StatusLine::StatusLine(const StatusLine& status_line)
{
    if (this == &status_line)
        return ;
    _http_version = status_line.getHttpVersion();
    _status_code = status_line.getStatusCode();
    _status_message = status_line.getStatusMessage();
    return ;
}

StatusLine::~StatusLine(void)
{

}

StatusLine& StatusLine::operator=(const StatusLine& status_line)
{
    if (this == &status_line)
        return (*this);
    _http_version = status_line.getHttpVersion();
    _status_code = status_line.getStatusCode();
    _status_message = status_line.getStatusMessage();
    return (*this);
}

int StatusLine::getStatusCode(void) const
{
    return (_status_code);
}

std::string StatusLine::getStatusMessage(void) const
{
    return (_status_message);
}

std::string StatusLine::getString(void)
{
    std::stringstream ss;
    ss << _status_code;
    return (_http_version + " " + ss.str() + " " + _status_message);
}

RequestLine::RequestLine(void)
{

}

RequestLine::RequestLine(const std::string& start_line)
{
    std::vector<std::string> arr;

    arr = ft::splitString(start_line, " ");
    _http_method = arr[0];
    _request_target = arr[1];
    if (arr.size() < 3)
        _http_version = "";
    else
        _http_version = arr[2];
}

RequestLine::RequestLine(const std::string& http_method, const std::string& request_target, const std::string& http_version)
: StartLine(http_version), _http_method(http_method), _request_target(request_target)
{

}

RequestLine::RequestLine(const RequestLine& request_line)
{
    if (this == &request_line)
        return ;
    _http_version = request_line.getHttpVersion();
    _http_method = request_line.getHttpMethod();
    _request_target = request_line.getRequestTarget();
    return ;
}

RequestLine::~RequestLine(void)
{

}

RequestLine& RequestLine::operator=(const RequestLine& request_line)
{
    if (this == &request_line)
        return (*this);
    _http_version = request_line.getHttpVersion();
    _http_method = request_line.getHttpMethod();
    _request_target = request_line.getRequestTarget();
    return (*this);
}

std::string RequestLine::getHttpMethod(void) const
{
    return (_http_method);
}

std::string RequestLine::getRequestTarget(void) const
{
    return (_request_target);
}

std::string RequestLine::getString(void)
{
    return (_http_method + " " + _request_target + " " + _http_version);
}

HttpMessage::HttpMessage(void)
 : _message_size(0), _chunked_size(0)
{

}

void HttpMessage::setHeaders(const std::string& header)
{
    std::vector<std::string> arr;
    std::string filed;
    std::string value;
    int pos;

    arr = ft::splitString(header, "\r\n");
    for (std::vector<std::string>::iterator it = arr.begin(); it < arr.end(); it++)
    {
        pos = (*it).find(':');
        filed = (*it).substr(0, pos);
        value = (*it).substr(pos + 2, (*it).length() - pos - 1);
        _headers[filed] = value;
    }
}

HttpMessage::HttpMessage(const std::string& http_message)
 : _message_size(0), _chunked_size(0)
{
    std::istringstream iss(http_message);
    std::string token;
    std::string s;

    std::getline(iss, token, '\n');
    while (std::getline(iss, token, '\n'))
    {
        s += token + "\n";
        if (token.compare("\r") == 0)
            break;
    }
    setHeaders(s);
    s.clear();
    while (std::getline(iss, token, '\n'))
        s += token + "\n";
    setMessageBody(s);
}

HttpMessage::HttpMessage(std::map<std::string, std::string>  headers, const std::string& message_body)
: _headers(headers), _message_body(message_body), _message_size(0), _chunked_size(0)
{
    _message_size = message_body.length();
    if (checkChunked())
        _chunked_message_body = mergeChunkedMessage(_message_body);
}

HttpMessage::HttpMessage(const HttpMessage& http_message)
{
    if (this == &http_message)
        return ;
    _headers = http_message._headers;
    _message_body = http_message._message_body;
    _message_size = http_message._message_size;
    _chunked_size = http_message._chunked_size;
    return ;
}

HttpMessage::~HttpMessage(void)
{

}

HttpMessage& HttpMessage::operator=(const HttpMessage& http_message)
{
    if (this == &http_message)
        return (*this);
    _headers = http_message._headers;
    _message_body = http_message._message_body;
    _message_size = http_message._message_size;
    _chunked_size = http_message._chunked_size;
    return (*this);
}

std::map<std::string, std::string> HttpMessage::getHeaders(void) const
{
    return (_headers);
}

std::string HttpMessage::mergeChunkedMessage(const std::string& chunk)
{
    std::vector<std::string> arr = ft::splitString(chunk, "\r\n");
    std::vector<std::string>::iterator it = arr.begin();
    std::string message;
    size_t chunk_size;

    _chunked_size = 0;
    message.reserve(_message_size);
    for (int i = 0; it != arr.end(); it++, i++)
    {
        if (i % 2 == 0)
        {
            chunk_size = ft::convertHex(*it);
            _chunked_size += chunk_size;
        }
        else if (chunk_size > 0)
            message += *it;
        else if (chunk_size == 0)
            break;
    }
    return (message);
}

std::string HttpMessage::getMessageBody(void)
{
    if (checkChunked())
        return (_chunked_message_body);
    return (_message_body);
}

void HttpMessage::setMessageBody(const std::string& message_body)
{
    std::string body = message_body;
    if (checkChunked())
        body = mergeChunkedMessage(message_body);
    _message_body = body;
    _message_size = _message_body.length();
}

size_t HttpMessage::getMessageSize(void) const
{
    if (checkChunked())
        return (_chunked_size);
    return (_message_size);
}

bool HttpMessage::checkChunked(void) const
{
    if (_headers.count("Transfer-Encoding") > 0)
    {
        if (_headers.find("Transfer-Encoding")->second == "chunked")
        {
            return (true);
        }
    }
    return (false);

}

void HttpMessage::changeChunkedMessage(size_t encoding_size)
{
    size_t add_size = encoding_size;
    size_t last_size = _message_size % encoding_size;
    size_t i;
    _headers["Transfer-Encoding"] = "chunked";
    if (_headers.count("Content-Length") > 0)
        _headers.erase("Content-Length");
    _chunked_message_body = "";
    for (i = 0; i < _message_size; i += encoding_size)
    {
        _chunked_message_body += ft::itos(add_size) + "\r\n";
        _chunked_message_body += _message_body.substr(i, i + add_size) + "\r\n";
    }
    i -= encoding_size;
    _chunked_message_body += ft::itos(last_size) + "\r\n";
    _chunked_message_body += _message_body.substr(i, i + last_size) + "\r\n";
    _chunked_message_body += "0\r\n\r\n";
    _chunked_size = _chunked_message_body.length();
}