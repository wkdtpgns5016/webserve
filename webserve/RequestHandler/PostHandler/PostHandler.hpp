#ifndef POSTHANDLER_HPP
#define POSTHANDLER_HPP

#include "../ServerHandler/ServerHandler.hpp"

class PostHandler : public ServerHandler
{
    private:
    public:
    PostHandler();
    PostHandler(ServerBlock* server_block, HttpRequestMessage request_message);
    PostHandler(const PostHandler& get_handler);
    ~PostHandler();
    PostHandler& operator=(const PostHandler& get_handler);

    HttpResponseMessage requestHandler();
};

#endif