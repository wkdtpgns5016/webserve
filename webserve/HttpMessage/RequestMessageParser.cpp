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

void RequestMessageParser::findTrailer(std::vector<std::string> arr, const std::string& trailer)
{
    std::string key = trailer + ": ";
    std::vector<std::string>::reverse_iterator it = arr.rbegin();
    if (arr.size() > 1)
    {
        if ((*it).find(key) != std::string::npos)
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
                if (isInvalidStartLine(_start_line_str))
                {
                    _request_message = HttpRequestMessage(_start_line_str);
                    throw InvalidRequestException();
                }
                _complete_start_line = true;
                _start_line = RequestLine(_start_line_str.substr(0, _start_line_str.length() - 2));
                _header_str = "\r\n";
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
        if (now == '\r' && prev == '\n')
            _header_end_flag = 3;
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

bool RequestMessageParser::isInvalidStartLine(const std::string& start_line)
{
    std::vector<std::string> arr = ft::splitString(start_line, " ");
    if (arr.size() != 3)
        return (true);
    if (arr[2] != "HTTP/1.1\r\n" && arr[2] != "HTTP/1.0\r\n")
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

const char* RequestMessageParser::InvalidRequestException::what() const throw()
{
    return ("InvalidRequestException");
}
