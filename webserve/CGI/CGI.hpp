#ifndef CGI_HPP
#define CGI_HPP

#include <map>
#include <string>
#include <unistd.h>
#include "../Configuration/LocationBlock/LocationBlock.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"

#define READ 0
#define WRITE 1


class CGI
{
private:
    LocationBlock                       *_block;
    HttpRequestMessage                  _request_message;
    std::map<std::string, std::string>  _env;

public:
    CGI(void);
    CGI(const CGI& obj);
    CGI operator=(const CGI& obj);
    ~CGI(void);

    CGI(LocationBlock *_block, HttpRequestMessage _request_message);

    void setEnv(void);
    char **getEnvChar(void) const;
    std::string excute(std::string scriptName);
};

#endif
