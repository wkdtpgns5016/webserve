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
    std::map<std::string, std::string> cgi_header;
    int status = 200;

    try
    {
        // http reqeust message 검사
        checkHttpMessage();
        // 임시
        if (path_info.find("/post_body") != std::string::npos)
            path = "test.bla";
        else
            path = findPath(path_info);
        message_body = executeCgi(path);
        // cgi response parse
        std::vector<std::string> arr = ft::splitString(message_body, "\r\n");
        cgi_header = getCgiHeader(arr);
        int cgi_status;
        if ((cgi_status = getStautsCgi(cgi_header)) > 0)
            status = cgi_status;
        message_body = arr.back();
        throwStatusError(status);
        // 응답 생성
        response_message = getResponseMessage(status, message_body, cgi_header);
    }
    catch(const Error400Exceptnion& e)
    {
        response_message = getErrorResponse(400);
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
