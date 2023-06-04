#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../CommonLogFormat/CommonLogFormat.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../../lib/ft/ft.hpp"

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"

class Logger
{
    public:
    static void writeLog(std::string client_ip, HttpRequestMessage request, HttpResponseMessage response);
    static void writeInfoLog(int socket_fd, std::string messsage);
    static void writeErrorLog(std::string messsage);
};

#endif