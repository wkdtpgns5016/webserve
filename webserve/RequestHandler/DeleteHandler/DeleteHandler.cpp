#include "DeleteHandler.hpp"

DeleteHandler::DeleteHandler() : ServerHandler()
{

}

DeleteHandler::DeleteHandler(ServerBlock* server_block, const HttpRequestMessage& request_message)
 : ServerHandler(server_block, request_message)
{

}

DeleteHandler::DeleteHandler(const DeleteHandler& delete_handler)
{
    _status = delete_handler._status;
    _request_message = delete_handler._request_message;
    _config = delete_handler._config;
}

DeleteHandler::~DeleteHandler()
{

}

DeleteHandler& DeleteHandler::operator=(const DeleteHandler& delete_handler)
{
    _status = delete_handler._status;
    _request_message = delete_handler._request_message;
    _config = delete_handler._config;
    return (*this);
}


void DeleteHandler::deleteFile(const std::string& request_target)
{
    std::string path;

	path = findPath(request_target);
    if (std::remove(path.c_str()) == -1)
    {
        Logger::writeErrorLog("File can not remove");
        throw Error500Exceptnion();
    }
}

HttpResponseMessage DeleteHandler::requestHandler()
{
    HttpResponseMessage response_message;
    std::string path;
    std::string request_target = _request_message.getStartLine().getRequestTarget();
    std::string path_info = _request_message.getPathInfo();
    std::map<std::string, std::string> cgi_header;

    try
    {
        int status = 200;
        std::string body;
        // http reqeust message 검사
        checkHttpMessage();
        if (!_config.getReturnValue().second.empty())
            return (redirectionHttpMessage());
        else
        {
            // 파일 삭제
            deleteFile(path_info);
            // 응답 생성
            if (body.empty())
                status = 201;
            response_message = getResponseMessage(status, body, cgi_header);
        }
    }
    catch(const Error400Exceptnion& e)
    {
        response_message = getErrorResponse(400);
    }
    catch(const Error403Exceptnion& e)
    {
        response_message = getErrorResponse(403);
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
    catch(const Error414Exceptnion& e)
    {
        response_message = getErrorResponse(414);
    }
    catch(const Error500Exceptnion& e)
    {
        response_message = getErrorResponse(500);
    }
    catch(const Error503Exceptnion& e)
    {
        response_message = getErrorResponse(503);
    }
    catch(const std::exception& e)
    {
        Logger::writeErrorLog(e.what());
        response_message = getErrorResponse(500);
    }
    return (response_message);
}
