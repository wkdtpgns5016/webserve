#include "PutHandler.hpp"

PutHandler::PutHandler() : ServerHandler()
{

}

PutHandler::PutHandler(ServerBlock* server_block, const HttpRequestMessage& request_message) : ServerHandler(server_block, request_message)
{

}

PutHandler::PutHandler(const PutHandler& put_handler)
{
    (void)put_handler;
}

PutHandler::~PutHandler()
{

}

PutHandler& PutHandler::operator=(const PutHandler& put_handler)
{
    (void)put_handler;
    return (*this);
}

int PutHandler::openFile(const std::string& path)
{
    int fd;
    if ((fd = open(path.c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR)) == -1)
        throw Error500Exceptnion();
    return (fd);
}

void PutHandler::writeFile(int fd, const std::string& message)
{
    if (write(fd, message.c_str(), message.length()) == -1)
    {
        close(fd);
        throw Error500Exceptnion();
    }
}

int PutHandler::putMethod()
{
    std::string request_target = _request_message.getStartLine().getRequestTarget();
    std::string path_info = _request_message.getPathInfo();
    std::string path;
    int status = 200;
    int fd;
    try
    {
        path = findPath(path_info);
        fd = openFile(path);
        writeFile(fd, _request_message.getMessageBody());
        close(fd);
        return (status);
    }
    catch(const Error404Exceptnion& e)
    {
        status = 201;
        path = _config.getRoot() + request_target;
        fd = openFile(path);
        writeFile(fd, _request_message.getMessageBody());
        close(fd);
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
    catch(const std::exception& e)
    {
        response_message = getErrorResponse(500);
    }
    return (response_message);
}
