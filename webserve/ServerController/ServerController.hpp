#ifndef SERVERCONTROLLER_HPP
#define SERVERCONTROLLER_HPP

#include "../lib/ft/ft.hpp"
#include "../HttpMessage/HttpRequestMessage.hpp"
#include "../HttpMessage/HttpResponseMessage.hpp"
#include "../Configuration/Conf/Conf.hpp"
#include "../Configuration/ConfigDto/ConfigDto.hpp"
#include "../RequestHandler/GetHandler/GetHandler.hpp"
#include "../RequestHandler/PostHandler/PostHandler.hpp"
#include "../RequestHandler/DeleteHandler/DeleteHandler.hpp"
#include "../RequestHandler/PutHandler/PutHandler.hpp"
#include <iostream>

class ServerController
{
    private:
    LocationBlock* findLocationBlock(std::vector<Block*> locations, std::string request_target);

    public:
    ServerController();
    ServerController(const ServerController& server_controller);
    ~ServerController();
    ServerController& operator=(const ServerController& server_controller);

    HttpResponseMessage requestHandler(ServerBlock* server_block, const std::string& http_message);
};

#endif