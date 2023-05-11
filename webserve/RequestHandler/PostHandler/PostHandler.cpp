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

HttpResponseMessage PostHandler::requestHandler()
{
    // 메소드 허용 검사
    // 파일 인지 cgi 검사
    // 파일 읽기
    // cgi 실행

    HttpResponseMessage response_message;
    int status_code = 200;
    std::string message_body = "Post";
    std::string request_target = _request_message.getStartLine().getRequestTarget();

        response_message = getResponseMessage(status_code, message_body);
    return (response_message);
}
