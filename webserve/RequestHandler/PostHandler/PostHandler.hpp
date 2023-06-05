#ifndef POSTHANDLER_HPP
#define POSTHANDLER_HPP

#include "../ServerHandler/ServerHandler.hpp"

class PostHandler : public ServerHandler
{
    private:
    void checkCGI(const std::string& path);

    public:
    PostHandler();
    PostHandler(ServerBlock* server_block, const HttpRequestMessage& request_message);
    PostHandler(const PostHandler& post_handler);
    ~PostHandler();
    PostHandler& operator=(const PostHandler& post_handler);

    HttpResponseMessage requestHandler();
};

#endif
