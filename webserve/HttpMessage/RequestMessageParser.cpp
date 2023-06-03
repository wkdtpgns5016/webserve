#include "RequestMessageParser.hpp"

RequestMessageParser::RequestMessageParser()
 : _is_chunked(false), _is_trailer(false), _complete_start_line(false), _complete_header(false), _complete_body(false)
 , _start_line_str(""), _header_str(""), _message_body_str(""), _start_line(), _header(), _request_message()
{

}

RequestMessageParser::RequestMessageParser(const RequestMessageParser& parser)
{
    _is_chunked = parser._is_chunked;
    _is_trailer = parser._is_trailer;
    _complete_start_line = parser._complete_start_line;
    _complete_header = parser._complete_header;
    _complete_body = parser._complete_body;
    _start_line_str = parser._start_line_str;
    _header_str = parser._header_str;
    _message_body_str = parser._message_body_str;
    _start_line = parser._start_line;
    _header = parser._header;
    _request_message = parser._request_message;
}

RequestMessageParser& RequestMessageParser::operator=(const RequestMessageParser& parser)
{
    _is_chunked = parser._is_chunked;
    _is_trailer = parser._is_trailer;
    _complete_start_line = parser._complete_start_line;
    _complete_header = parser._complete_header;
    _complete_body = parser._complete_body;
    _start_line_str = parser._start_line_str;
    _header_str = parser._header_str;
    _message_body_str = parser._message_body_str;
    _start_line = parser._start_line;
    _header = parser._header;
    _request_message = parser._request_message;
    return (*this);
}

RequestMessageParser::~RequestMessageParser()
{

}

void RequestMessageParser::checkChunk()
{
    if (_header.count("Transfer-Encoding") > 0)
    {
        if (_header["Transfer-Encoding"] == "chunked")
        {
            _is_chunked = true;
        }
    }
}

void RequestMessageParser::checkTrailer()
{
    if (_header.count("Trailer") > 0)
        _is_trailer = true;
}

void RequestMessageParser::checkChunkComplete(const std::string&  message, size_t len)
{
    // trailer 헤더가 있을 경우
    std::string trailer;
    std::vector<std::string> line;
    size_t l = _message_body_str.length();

    if (_is_trailer)
    {
        trailer = _header["Trailer"];
        findTrailer(line, _header["Trailer"]);
    }
    else
    {
        if (len >= 5)
            findZero(message, len);
        else if (l >= 5)
            findZero(_message_body_str, l);
    }
}

void RequestMessageParser::findZero(const std::string&  message, size_t len)
{
    if (message.at(len - 1) != '\n')
        return ;
    if (message.at(len - 2) != '\r')
        return ;
    if (message.at(len - 3) != '\n')
        return ;
    if (message.at(len - 4) != '\r')
        return ;
    if (message.at(len - 5) != '0')
        return ;
    _complete_body = true;
}

void RequestMessageParser::findTrailer(std::vector<std::string> arr, std::string trailer)
{
    std::string key = trailer + ": ";
    std::vector<std::string>::reverse_iterator it = arr.rbegin();
    if (arr.size() > 1)
    {
        if ((*it).find(key) != std::string::npos)
            _complete_body = true;
    }
}

void RequestMessageParser::initStartLine(const std::string&  message)
{
    size_t pos;
    std::string prev;
    std::string next;

    _start_line_str += message;
    if ((pos = _start_line_str.find("\r\n")) != std::string::npos)
    {
        prev = _start_line_str.substr(0, pos);
        if (prev.length() < _start_line_str.length() - 2)
            next = _start_line_str.substr(pos + 2);
        _start_line_str = prev;
        _start_line = RequestLine(_start_line_str);
        _complete_start_line = true;
        initHeader(next);
    }
}

void RequestMessageParser::initHeader(const std::string&  message)
{
    size_t pos;
    std::string prev;
    std::string next;

    _header_str += message;
    if ((pos = _header_str.find("\r\n\r\n")) != std::string::npos)
    {
        prev = _header_str.substr(0, pos + 4);
        if (prev.length() < _header_str.length())
            next = _header_str.substr(pos + 4);
        _header_str = prev;
        setHeader(_header_str);
        _complete_header = true;
        checkChunk();
        checkTrailer();
        initBody(next, next.length());
    }
}

void RequestMessageParser::initBody(const std::string& message, size_t len)
{
    _message_body_str += message;
    if (_is_chunked)
        checkChunkComplete(message, len);
    else
    {
        if (_header.count("Content-Length") > 0)
        {
            size_t content_size = ft::stoi(_header["Content-Length"]);
            if (_message_body_str.length() >= content_size)
                _complete_body = true;
        }
        else
            _complete_body = true;
    }
}

void RequestMessageParser::setHeader(const std::string&  message)
{
    std::vector<std::string> arr;
    std::string filed;
    std::string value;
    int pos;

    arr = ft::splitString(message, "\r\n");
    for (std::vector<std::string>::iterator it = arr.begin(); it < arr.end(); it++)
    {
        pos = (*it).find(':');
        filed = (*it).substr(0, pos);
        value = (*it).substr(pos + 2, (*it).length() - pos - 1);
        _header[filed] = value;
    }
}

void RequestMessageParser::appendMessage(const std::string&  new_str, size_t len)
{
    if (!_complete_start_line)
        initStartLine(new_str);
    else if (!_complete_header)
        initHeader(new_str);
    else if (!_complete_body)
        initBody(new_str, len);
    if (_complete_start_line && _complete_header && _complete_body)
        _request_message = HttpRequestMessage(_start_line, _header, _message_body_str);
}

HttpRequestMessage RequestMessageParser::getRequestMessage() const
{
    return (_request_message);
}

bool        RequestMessageParser::checkMessage() const
{
    if (_complete_start_line && _complete_header && _complete_body)
        return (true);
    return (false);
}
