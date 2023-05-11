#include "DeleteHandler.hpp"

DeleteHandler::DeleteHandler() : ServerHandler()
{

}

DeleteHandler::DeleteHandler(ServerBlock* server_block, HttpRequestMessage request_message)
 : ServerHandler(server_block, request_message)
{

}

DeleteHandler::DeleteHandler(const DeleteHandler& delete_handler)
{
    (void)delete_handler;
}

DeleteHandler::~DeleteHandler()
{

}

DeleteHandler& DeleteHandler::operator=(const DeleteHandler& delete_handler)
{
    (void)delete_handler;
    return (*this);
}

HttpResponseMessage DeleteHandler::requestHandler()
{
    HttpResponseMessage response_message;
    std::string path;
    std::string request_target = _request_message.getStartLine().getRequestTarget();

    try
    {
        // 메소드 권한 검사
        checkAllowMethod("DELETE");
        // 파일 삭제
        path = findPath(request_target);
        // 응답 생성
        response_message = getResponseMessage(200, "");
    }
    catch(const Error404Exceptnion& e)
    {
        response_message = getErrorResponse(404);
    }
    catch(const Error405Exceptnion& e)
    {
        response_message = getErrorResponse(405);
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
