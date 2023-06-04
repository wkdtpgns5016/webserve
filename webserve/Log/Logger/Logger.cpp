#include "Logger.hpp"

void Logger::writeLog(std::string client_addr, HttpRequestMessage request, HttpResponseMessage response)
{
    std::string log_message;
    CommonLogFormat log = CommonLogFormat(client_addr, request, response);
    log_message = log.getString();
    std::cout << GRN << log_message << NC << std::endl;
}

void Logger::writeInfoLog(int socket_fd, std::string messsage)
{
    std::string log_message;
    std::vector<std::string> arr = ft::getTime(std::time(NULL));
    std::string time_stamp = "[" + arr[2] + "/"
                + arr[1] + "/"
                + arr[4].substr(0, arr[4].length() - 1) + ":"
                + arr[3] + " +0900]";

    log_message = "[INFO]    " + time_stamp + "    " + messsage + " [" + ft::itos(socket_fd) + "]";
    std::cout << CYN << log_message << NC << std::endl;
}

void Logger::writeErrorLog(std::string messsage)
{
    std::string log_message;
    std::vector<std::string> arr = ft::getTime(std::time(NULL));
    std::string time_stamp = "[" + arr[2] + "/"
                + arr[1] + "/"
                + arr[4].substr(0, arr[4].length() - 1) + ":"
                + arr[3] + " +0900]";

    log_message = "[ERROR]   " + time_stamp + "    " + messsage;
    std::cerr << RED << log_message << NC << std::endl;
}