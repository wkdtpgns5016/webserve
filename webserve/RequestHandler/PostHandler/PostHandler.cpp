#include "PostHandler.hpp"

PostHandler::PostHandler() : ServerHandler()
{

}

PostHandler::PostHandler(ServerBlock* server_block, HttpRequestMessage request_message)
 : ServerHandler(server_block, request_message)
{

}

PostHandler::PostHandler(const PostHandler& delete_handler)
{
    (void)delete_handler;
}

PostHandler::~PostHandler()
{

}

PostHandler& PostHandler::operator=(const PostHandler& delete_handler)
{
    (void)delete_handler;
    return (*this);
}
void PostHandler::checkCGI(std::string request_target)
{
    (void)request_target;
}

HttpResponseMessage PostHandler::requestHandler()
{
    HttpResponseMessage response_message;
    std::string message_body;
    std::string path;
    std::string request_target = _request_message.getStartLine().getRequestTarget();
    std::string path_info = _request_message.getPathInfo();

    try
    {
        // http reqeust message 검사
        checkHttpMessage();
        path = findPath(path_info);
        message_body = executeCgi(path_info);
        // 응답 생성
        response_message = getResponseMessage(200, message_body);
    }
    catch(const Error400Exceptnion& e)
    {
        response_message = getResponseMessage(400, "");
    }
    catch(const Error404Exceptnion& e)
    {
        response_message = getErrorResponse(404);
    }
    catch(const Error405Exceptnion& e)
    {
        response_message = getErrorResponse(405);
    }
    catch(const Error413Exceptnion& e)
    {
        response_message = getErrorResponse(413);
    }
    catch(const Error500Exceptnion& e)
    {
        response_message = getErrorResponse(500);
    }
    catch(const Error503Exceptnion& e)
    {
        response_message = getErrorResponse(503);
    }
    return (response_message);
}
