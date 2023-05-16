#ifndef DELETEHANDLER_HPP
#define DELETEHANDLER_HPP

#include "../ServerHandler/ServerHandler.hpp"

class DeleteHandler : public ServerHandler
{
    private:
    void deleteFile(std::string request_target);

    public:
    DeleteHandler();
    DeleteHandler(ServerBlock* server_block, HttpRequestMessage request_message);
    DeleteHandler(const DeleteHandler& get_handler);
    ~DeleteHandler();
    DeleteHandler& operator=(const DeleteHandler& get_handler);

    HttpResponseMessage requestHandler();
};

#endif