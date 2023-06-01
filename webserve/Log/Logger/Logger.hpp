#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../CommonLogFormat/CommonLogFormat.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../../lib/ft/ft.hpp"

class Logger
{
    public:
    static void writeLog(std::string client_ip, HttpRequestMessage request, HttpResponseMessage response, int write_fd);
    static void writeLog(std::string addr, int socket_fd, std::string messsage, int write_fd);
};

#endif