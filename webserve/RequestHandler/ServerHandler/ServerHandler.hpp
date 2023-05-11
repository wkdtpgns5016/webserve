#ifndef SERVER_CONTROLLER_HPP
#define SERVER_CONTROLLER_HPP

#include "../lib/ft/ft.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"
#include "../Configuration/Conf/Conf.hpp"
#include "../Configuration/ConfigDto/ConfigDto.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <ctime>
#include <algorithm>
#include <map>
#include <exception>

class ServerHandler
{
    protected:
    std::map<int, std::string>  _status;
    HttpRequestMessage          _request_message;
    LocationBlock*              _b_config;
    ConfigDto                   _config;

    void init_status();
    LocationBlock* findLocationBlock(std::vector<Block*> locations, std::string request_target);

    void checkAllowMethod(std::string method);
    bool checkDirectory(std::string path);
    bool checkFile(std::string request_target);

    std::vector<std::string> getIndexPath(std::string root, std::string index);
    std::string findPath(std::string request_target);

    std::string executeCgi(std::string request_target);

    HttpResponseMessage getErrorResponse(int status_code);
    HttpResponseMessage getResponseMessage(int status_code, std::string message_body);
    
    public:
    ServerHandler();
    ServerHandler(ServerBlock* server_block, HttpRequestMessage request_message);
    ServerHandler(const ServerHandler& server_handler);
    ServerHandler& operator=(const ServerHandler& server_handler);
    virtual ~ServerHandler();

    HttpRequestMessage& getRequestMessage(void);
    virtual HttpResponseMessage requestHandler() = 0;

    class AutoIndexExceptnion : public std::exception {
			public:
				virtual const char* what() const throw();
		};
    class Error404Exceptnion : public std::exception {
			public:
				virtual const char* what() const throw();
		};
    class Error405Exceptnion : public std::exception {
			public:
				virtual const char* what() const throw();
		};
    class Error500Exceptnion : public std::exception {
			public:
				virtual const char* what() const throw();
		};
    class Error503Exceptnion : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

#endif