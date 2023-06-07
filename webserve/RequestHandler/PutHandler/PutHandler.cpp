#include "PutHandler.hpp"

PutHandler::PutHandler() : ServerHandler()
{

}

PutHandler::PutHandler(ServerBlock* server_block, const HttpRequestMessage& request_message) : ServerHandler(server_block, request_message)
{

}

PutHandler::PutHandler(const PutHandler& put_handler)
{
    _status = put_handler._status;
    _request_message = put_handler._request_message;
    _config = put_handler._config;
}

PutHandler::~PutHandler()
{

}

PutHandler& PutHandler::operator=(const PutHandler& put_handler)
{
    _status = put_handler._status;
    _request_message = put_handler._request_message;
    _config = put_handler._config;
    return (*this);
}

void PutHandler::writeFile(const std::string& path, const std::string& message)
{
	std::ofstream out(path);
    if (out.is_open())
    {
        out.clear();
        out << message;
        out.close();
    }
    else
    {
        Logger::writeErrorLog("File can not open");
        throw Error500Exceptnion();
    }
}

int PutHandler::putMethod()
{
    std::string request_target = _request_message.getStartLine().getRequestTarget();
    std::string path_info = _request_message.getPathInfo();
    std::string path;
    int status = 200;
    try
    {
        path = findPath(path_info);
        writeFile(path, _request_message.getMessageBody());
        return (status);
    }
    catch(const Error404Exceptnion& e)
    {
        status = 201;
        path = _config.getRoot() + request_target;
        writeFile(path, _request_message.getMessageBody());
        return (status);
    }
    return (status);
}

HttpResponseMessage PutHandler::requestHandler()
{
    HttpResponseMessage response_message;
    std::string message_body;
    std::map<std::string, std::string> cgi_header;
    int status;
    try
    {
        checkHttpMessage();
        if (!_config.getReturnValue().second.empty())
            return (redirectionHttpMessage());
        else
        {
            status = putMethod();
            if (message_body.empty())
                status = 204;
            response_message = getResponseMessage(status, message_body, cgi_header);
        }
    }
    catch(const Error400Exceptnion& e)
    {
        response_message = getErrorResponse(400);
    }
    catch(const Error403Exceptnion& e)
    {
        response_message = getErrorResponse(400);
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
