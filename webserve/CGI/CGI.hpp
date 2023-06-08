#ifndef CGI_HPP
#define CGI_HPP

#include <map>
#include <fcntl.h>
#include <string>
#include <unistd.h>
#include "../Configuration/ConfigDto/ConfigDto.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../Log/Logger/Logger.hpp"

#define READ 0
#define WRITE 1


class CGI
{
private:
    ConfigDto                           _config;
    HttpRequestMessage                  _request_message;
    std::map<std::string, std::string>  _env;

    void initEnv(void);
    void setEnv(void);
    char **getEnvChar(void) const;
public:
    CGI(void);
    CGI(const CGI& obj);
    CGI operator=(const CGI& obj);
    ~CGI(void);
    CGI(ConfigDto _config, HttpRequestMessage _request_message);
    
    std::string excute(std::string scriptName);
};

#endif
