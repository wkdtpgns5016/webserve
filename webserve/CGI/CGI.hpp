#ifndef CGI_HPP
#define CGI_HPP

#include <map>
#include <string>
#include <unistd.h>
#include "../lib/ft/splitString.cpp"
#include "../ServerParser/ServerParser.hpp"
#include "../LocationParser/LocationParser.hpp"
#include "../ServerHandler/ServerHandler.hpp"

#define READ 0
#define WRITE 1


class CGI
{
private:
    ServerParser                        _s_parser;
    LocationParser                      _l_parser;
    ServerHandler                       _s_handler;
    std::map<std::string, std::string>  _env;

public:
    CGI(void);
    CGI(const CGI& obj);
    CGI operator=(const CGI& obj);
    ~CGI(void);

    CGI(ServerParser s_parser, LocationParser l_parser, ServerHandler s_handler);

    void setEnv(void);
    char **getEnvChar(void) const;
    std::string excute(std::string scriptName);
};

#endif
