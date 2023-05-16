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


void DeleteHandler::deleteFile(std::string request_target)
{
    std::string path;

    path = findPath(request_target);
    if (remove(path.c_str()) == -1)
        throw Error500Exceptnion();
}

HttpResponseMessage DeleteHandler::requestHandler()
{
    HttpResponseMessage response_message;
    std::string path;
    std::string request_target = _request_message.getStartLine().getRequestTarget();

    try
    {
        int status = 200;
        std::string body;
        // 메소드 권한 검사
        checkAllowMethod(_request_message.getStartLine().getHttpMethod());
        // 파일 삭제
        deleteFile(request_target);
        // 응답 생성
        if (body.empty())
            status = 201;
        response_message = getResponseMessage(status, body);
    }
    catch(const Error404Exceptnion& e)
    {
        response_message = getResponseMessage(204, "");
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
