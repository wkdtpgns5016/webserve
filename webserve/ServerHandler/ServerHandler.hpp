#ifndef SERVER_CONTROLLER_HPP
#define SERVER_CONTROLLER_HPP

#include "../lib/ft/ft.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"
#include "../Configuration/Conf/Conf.hpp"
#include "../Configuration/Block/Block.hpp"
#include "../Configuration/ServerBlock/ServerBlock.hpp"
#include "../Configuration/LocationBlock/LocationBlock.hpp"
#include <unistd.h>
#include <algorithm>
#include <map>
#include <exception>

class ServerHandler
{
    private:
    std::map<int, std::string>  _status;
    HttpRequestMessage          _request_message;
    ServerBlock*                _server_block;
    LocationBlock*              _location_block;

    void init_status();
    bool checkFile(std::string request_target);

    std::vector<std::string> getIndexPath(std::string root, std::string index);
    LocationBlock* findLocationBlock(std::vector<Block*> locations, std::string request_target);
    bool checkAllowMethod(std::string method);

    std::string findPath(std::string request_target);
    std::string openFile(std::string request_target);
    std::string executeCgi(std::string request_target);

    std::string getErrorPage(int status_code);

    HttpResponseMessage getHandler();
    HttpResponseMessage postHandler();
    HttpResponseMessage deleteHandler();

    ServerHandler(const ServerHandler& server_handler);
    ServerHandler& operator=(const ServerHandler& server_handler);

    public:
    ServerHandler();
    ServerHandler(ServerBlock* server_block, std::string http_message);
    ~ServerHandler();

    HttpRequestMessage& getRequestMessage(void);
    HttpResponseMessage getResponseMessage(int status_code, std::string message_body);
    HttpResponseMessage requestHandler();

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
};

#endif