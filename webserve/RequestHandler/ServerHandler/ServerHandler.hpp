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
    ConfigDto                   _config;

    void init_status();
    LocationBlock* findLocationBlock(const std::vector<Block*>& locations, const std::string& request_target);

    std::string cleanUrl(const std::string& url, bool request_target);

    void checkAllowMethod(const std::string& method);
    void checkHttpVersion(const RequestLine& start_line);
    void checkMessageSize(void);
    void checkHttpMessage(void);
    bool checkDirectory(const std::string& path);
    int checkFile(const std::string& request_target);

    std::vector<std::string> getIndexPath(const std::string& root, const std::string& index);
    std::string tryFiles(const std::vector<std::string>& try_files);
    std::string findPath(const std::string& request_target);

    std::string executeCgi(const std::string& file_path);
    HttpResponseMessage getCgiResponse(int status, const std::string& message_body);
    std::map<std::string, std::string> getCgiHeader(const std::string& cgi_header_str);
    int getStautsCgi(const std::map<std::string, std::string>& cgi_header);
    std::map<std::string, std::string> setHeader(int status_code, const std::string& message_body, const std::map<std::string, std::string>& cgi_header);
    
    void                throwStatusError(int status_code);
    HttpResponseMessage getErrorResponse(int status_code);
    HttpResponseMessage getResponseMessage(int status_code, const std::string& message_body, const std::map<std::string, std::string>& cgi_header);
    
    public:
    ServerHandler();
    ServerHandler(ServerBlock* server_block, const HttpRequestMessage& request_message);
    ServerHandler(const ServerHandler& server_handler);
    ServerHandler& operator=(const ServerHandler& server_handler);
    virtual ~ServerHandler();

    const HttpRequestMessage& getRequestMessage(void);
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
