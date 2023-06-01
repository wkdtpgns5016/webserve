#include "Logger.hpp"

void Logger::writeLog(std::string client_addr, HttpRequestMessage request, HttpResponseMessage response, int write_fd)
{
    CommonLogFormat log = CommonLogFormat(client_addr, request, response);
    log.wirteLogMessage(write_fd);
}

void Logger::writeLog(std::string addr, int socket_fd, std::string messsage, int write_fd)
{
    std::string log_message;
    std::vector<std::string> arr = ft::getTime(std::time(NULL));
    std::string time_stamp = "[" + arr[2] + "/"
                + arr[1] + "/"
                + arr[4].substr(0, arr[4].length() - 1) + ":"
                + arr[3] + " +0900]";

    log_message = addr + " " + time_stamp + " : " + messsage + " [" + ft::itos(socket_fd) + "]\n";
    write(write_fd, log_message.c_str(), log_message.length());
}