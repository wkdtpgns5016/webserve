#ifndef HTTP_REQUEST_MESSAGE_HPP
#define HTTP_REQUEST_MESSAGE_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stdio.h>

/**
 * HTTP REQUEST METHOD
 */
enum request_method
{
    GET = 0,
    POST = 1
};

/**
 * REQUSET LINE
 */
typedef struct request_line
{
    request_method method;
    std::string url;
    std::string version;

    request_line() { }
    request_line(std::string request_line)
    {
        std::istringstream ss(request_line);
        std::vector<std::string> result;
        std::string temp;
 
        while (std::getline(ss, temp, ' ')) 
            result.push_back(temp);
        if (!result.at(0).compare("GET"))
            method = GET;
        else if (!result.at(0).compare("POST"))
            method = POST;
        url = result.at(1);
        version = result.at(2);
    }
} request_line;

/**
 * REQUSET MESSAGE HEADER
 */
typedef struct request_message_header
{
    request_line request_line;
    std::string request_header;

    request_message_header() : request_line() {};
} request_message_header;

/**
 * HTTP REQUSET MESSAGE
 */
class http_request_message
{
    public:
    request_message_header header;
    std::string body;

    http_request_message(std::string messages)
    {
        std::stringstream ss(messages);
        std::vector<std::string> result;
        std::string temp;
        int i = 1;
 
        while (std::getline(ss, temp, '\n'))
        {
            result.push_back(temp);
        }

        header.request_line = request_line(result.at(0));
        temp = "";
        while (result.at(i).length() != 1)
        {
            temp += result.at(i) + "\n";
            i++;
        }
        header.request_header = temp;
        temp = "";
        if (result.size() > i + 1)
        {
            i++;
            while (i < result.size())
            {
                temp += result.at(i);
                i++;
            }
        }
        body = temp;
    }
};

#endif