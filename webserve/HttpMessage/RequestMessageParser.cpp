#include "RequestMessageParser.hpp"

RequestMessageParser::RequestMessageParser()
 : _is_chunked(false), _is_trailer(false), _complete_start_line(false), _complete_header(false), _complete_body(false)
 , _start_line_str(""), _header_str(""), _message_body_str(""), _start_line(), _header(), _request_message()
{
    _start_line_end_flag = 0;
    _header_end_flag = 0;
    _message_body_len = 0;
    _chunk_end_flag = 0;
    _prev = 0;
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
    _start_line_end_flag = parser._start_line_end_flag;
    _header_end_flag = parser._header_end_flag;
    _message_body_len = parser._message_body_len;
    _chunk_end_flag = parser._chunk_end_flag;
    _prev = parser._prev;
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
    _start_line_end_flag = parser._start_line_end_flag;
    _header_end_flag = parser._header_end_flag;
    _message_body_len = parser._message_body_len;
    _chunk_end_flag = parser._chunk_end_flag;
    _prev = parser._prev;
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

    std::cout << std::clock() << "              start initStartLine" << std::endl;
    _start_line_str += message;
    std::cout << std::clock() << "              start find" << std::endl;
    if ((pos = _start_line_str.find("\r\n")) != std::string::npos)
    {
        std::cout << std::clock() << "              end find" << std::endl;
        prev = _start_line_str.substr(0, pos);
        if (prev.length() < _start_line_str.length() - 2)
            next = _start_line_str.substr(pos + 2);
        _start_line_str = prev;
        _start_line = RequestLine(_start_line_str);
        _complete_start_line = true;
        initHeader(next);
    }
    std::cout << std::clock() << "              end initStartLine" << std::endl;
}

void RequestMessageParser::initHeader(const std::string&  message)
{
    size_t pos;
    std::string prev;
    std::string next;

    std::cout << std::clock() << "              start initHeader" << std::endl;
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
    std::cout << std::clock() << "              end initHeader" << std::endl;
}

void RequestMessageParser::initBody(const std::string& message, size_t len)
{
    std::cout << std::clock() << "              start initBody" << std::endl;
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
    std::cout << std::clock() << "              end initBody" << std::endl;
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
    std::cout << std::clock() << "              start appendMessage" << std::endl;
    if (!_complete_start_line)
        initStartLine(new_str);
    else if (!_complete_header)
        initHeader(new_str);
    else if (!_complete_body)
        initBody(new_str, len);
    if (_complete_start_line && _complete_header && _complete_body)
        _request_message = HttpRequestMessage(_start_line, _header, _message_body_str);
    std::cout << std::clock() << "              end appendMessage" << std::endl;
}

void RequestMessageParser::appendMessage(char* buffer, size_t len)
{
    char now = 0;
    size_t i = 0;
    while (i < len)
    {
        now = buffer[i];
        if (!_complete_start_line)
        {
            _start_line_str.push_back(now);
            if (checkStartLineEnd(_prev, now))
            {
                _complete_start_line = true;
                _start_line = RequestLine(_start_line_str.substr(0, _start_line_str.length() - 2));
            }
        }
        else if (!_complete_header)
        {
            _header_str.push_back(now);
            if (checkHeaderEnd(_prev, now))
            {
                _complete_header = true;
                setHeader(_header_str);
                checkChunk();
                checkTrailer();
                if (checkBodyEnd(_prev, now))
                    _complete_body = true;
            }

        }
        else if (!_complete_body)
        {
            _message_body_str.push_back(now);
            _message_body_len++;
            if (checkBodyEnd(_prev, now))
                _complete_body = true;
        }
        _prev = buffer[i];
        i++;
        if (_complete_start_line && _complete_header && _complete_body)
            break ;
    }
    if (_complete_start_line && _complete_header && _complete_body)
        _request_message = HttpRequestMessage(_start_line, _header, _message_body_str);
}

bool RequestMessageParser::checkStartLineEnd(char prev, char now)
{
    switch (_start_line_end_flag)
    {
    case 0:
        if (now == '\r')
            _start_line_end_flag++;
        break;
    case 1:
        if (now == '\n' && prev == '\r')
            _start_line_end_flag++;
        break;
    default:
        break;
    }
    if (_start_line_end_flag == 2)
        return (true);
    return (false);
}

bool RequestMessageParser::checkHeaderEnd(char prev, char now)
{
    switch (_header_end_flag)
    {
    case 0:
        if (now == '\r')
            _header_end_flag++;
        break;
    case 1:
        if (now == '\n' && prev == '\r')
            _header_end_flag++;
        break;
    case 2:
        if (now == '\r' && prev == '\n')
            _header_end_flag++;
        break;
    case 3:
        if (now == '\n' && prev == '\r')
            _header_end_flag++;
        break;
    default:
        break;
    }
    if (_header_end_flag == 4)
        return (true);
    return (false);
}

bool RequestMessageParser::checkBodyEnd(char prev, char now)
{
    if (_is_chunked)
        return (checkChunkEnd(prev, now));
    else
    {
        if (_header.count("Content-Length") > 0)
        {
            size_t content_size = ft::stoi(_header["Content-Length"]);
            if (_message_body_len >= content_size)
                return (true);
        }
        else
            return (true);
    }
    return (false);
}

bool RequestMessageParser::checkChunkEnd(char prev, char now)
{
    switch (_chunk_end_flag)
    {
    case 0:
        if (now == '0')
            _chunk_end_flag++;
        break;
    case 1:
        if (now == '\r' && prev == '0')
            _chunk_end_flag++;
        break;
    case 2:
        if (now == '\n' && prev == '\r')
            _chunk_end_flag++;
        break;
    case 3:
        if (now == '\r' && prev == '\n')
            _chunk_end_flag++;
        break;
    case 4:
        if (now == '\n' && prev == '\r')
            _chunk_end_flag++;
        break;
    default:
        break;
    }
    if (_chunk_end_flag == 5)
        return (true);
    return (false);
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
