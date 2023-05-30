#ifndef SERVER_HANDLER_HPP
#define SERVER_HANDLER_HPP

#include "../lib/ft/ft.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"
#include "../Configuration/Conf/Conf.hpp"
#include "../Configuration/ConfigDto/ConfigDto.hpp"
#include "../CGI/CGI.hpp"

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

    std::string cleanUrl(std::string url, bool request_target);

    void checkAllowMethod(std::string method);
    void checkHttpVersion(RequestLine start_line);
    void checkMessageSize(void);
    void checkHttpMessage(void);
    bool checkDirectory(std::string path);
    int checkFile(std::string request_target);

    std::vector<std::string> getIndexPath(std::string root, std::string index);
    std::string tryFiles(std::vector<std::string> try_files);
    std::string findPath(std::string request_target);

    std::string executeCgi(std::string file_path);
    std::map<std::string, std::string> getCgiHeader(std::vector<std::string> arr);
    int getStautsCgi(std::map<std::string, std::string> cgi_header);

    std::map<std::string, std::string> setHeader(int status_code, std::string message_body, std::map<std::string, std::string> cgi_header);
    
    void                throwStatusError(int status_code);
    HttpResponseMessage getErrorResponse(int status_code);
    HttpResponseMessage getResponseMessage(int status_code, std::string message_body, std::map<std::string, std::string> cgi_header);
    
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
    class Error400Exceptnion : public std::exception {
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
    class Error413Exceptnion : public std::exception {
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