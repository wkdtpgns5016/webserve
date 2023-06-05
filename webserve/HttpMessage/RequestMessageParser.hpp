#ifndef REQUESTMESSAGEPARSER_HPP
#define REQUESTMESSAGEPARSER_HPP

#include "../HttpMessage/HttpRequestMessage.hpp"
#include <iostream>
#include <unistd.h>

class RequestMessageParser
{
    private:
    bool        _is_chunked;
    bool        _is_trailer;
    bool        _complete_start_line;
    int         _start_line_end_flag;
    bool        _complete_header;
    int         _header_end_flag;
    bool        _complete_body;
    int         _chunk_end_flag;

    char        _prev;

    std::string _start_line_str;
    std::string _header_str;
    std::string _message_body_str;
    size_t      _message_body_len;

    RequestLine _start_line;
    std::map<std::string, std::string> _header;

    HttpRequestMessage _request_message;
    
    void checkChunk();
    void checkTrailer();
    void findTrailer(std::vector<std::string> arr, const std::string& trailer);

    void setHeader(const std::string& message);
    bool checkStartLineEnd(char prev, char now);
    bool checkHeaderEnd(char prev, char now);
    bool checkBodyEnd(char prev, char now);
    bool checkChunkEnd(char prev, char now);

    bool isInvalidStartLine(const std::string& start_line);

    public:
    RequestMessageParser();
    RequestMessageParser(const RequestMessageParser& parser);
    RequestMessageParser& operator=(const RequestMessageParser& parser);
    ~RequestMessageParser();

    void appendMessage(char* buffer, size_t len);
    HttpRequestMessage getRequestMessage() const;
    bool        checkMessage() const;

    class InvalidRequestException : public std::exception {
        public:
            virtual const char* what() const throw();
	};
};

#endif