#include "GetHandler.hpp"

GetHandler::GetHandler() : ServerHandler()
{

}

GetHandler::GetHandler(ServerBlock* server_block, HttpRequestMessage request_message)
 : ServerHandler(server_block, request_message)
{

}

GetHandler::GetHandler(const GetHandler& get_handler)
{
    (void)get_handler;
}

GetHandler::~GetHandler()
{

}

GetHandler& GetHandler::operator=(const GetHandler& get_handler)
{
    (void)get_handler;
    return (*this);

}

std::string GetHandler::openFile(std::string request_target)
{
    std::string message_body;
    std::string file_path = findPath(request_target);
    // autoindex 유무
    if (checkDirectory(file_path))
    {
        if (_config.getAutoindex())
            message_body = getAutoIndexPage(file_path, request_target);
        else
            throw Error404Exceptnion();
    }
    else
        message_body = ft::readFileIntoString(file_path);
    return (message_body);
}

std::string GetHandler::getAutoIndexPage(std::string path, std::string request_target)
{
    std::string message;

    message = "<!DOCTYPE html><html><head><title>";
    message += request_target + "</title></head><body>";
    message += "<h1>index of "+ request_target;
    if (request_target.back() != '/')
        message += "/";
    message += "</h1><hr />";
    message += getDirectoryList(path);
    message += "<hr /></body></html>";
    return (message);
}

std::string GetHandler::getDirectoryList(std::string path)
{
    std::stringstream ss;
    std::string file_name;
    std::string file_path;
    DIR *dp = NULL;
    struct dirent* entry = NULL;

    if ((dp = opendir(path.c_str())) == NULL)
        throw Error503Exceptnion();
    ss << "<table>";
    while ((entry = readdir(dp)) != NULL)
    {
        struct stat buf;
        ss << "<tr>";
        if (std::strcmp(entry->d_name, ".") == 0)
            continue ;
        // file 이름
        file_name = std::string(entry->d_name);
        file_path = path;
        if (file_path.back() != '/')
            file_path += "/";
        file_path += file_name;
        if (checkDirectory(file_path))
            file_name += "/";
        ss << "<td width=\"300\"><a href=" << file_name << ">" << file_name << "</a></td>";
        if (std::strcmp(entry->d_name, "..") == 0)
        {
            ss << "<td width=\"200\"></td>";
            ss << "<td width=\"100\"></td></tr>";
            continue ;
        }
        lstat(file_path.c_str(), &buf);
        // file 수정 시간
        ss << "<td width=\"200\">" << std::ctime(&buf.st_ctimespec.tv_sec) << "</td>";
        // file 크기
        ss << "<td width=\"100\">" << buf.st_size << "</td>"; 
        ss << "</tr>";
    }
    ss << "</table>";
    return (ss.str());
}

HttpResponseMessage GetHandler::requestHandler()
{
    HttpResponseMessage response_message;
    std::string message_body;
    std::string request_target = _request_message.getStartLine().getRequestTarget();
    std::string path_info = _request_message.getPathInfo();
    std::map<std::string, std::string> cgi_header;
    int status = 200;

    try
    {
        // http reqeust message 검사
        checkHttpMessage();
        // 파일 종류 판별
        if (checkFile(path_info) == -1) // 일반 파일
            message_body = openFile(path_info);
        else                           // cgi 파일
        {
            std::string path = findPath(path_info);
            message_body = executeCgi(path);
            if (!message_body.empty())
            {
                std::vector<std::string> arr = ft::splitString(message_body, "\r\n");
                cgi_header = getCgiHeader(arr);
                int cgi_status;
                if ((cgi_status = getStautsCgi(cgi_header)) > 0)
                    status = cgi_status;
                message_body = arr.back();
                throwStatusError(status);
            }
        }
        // 응답 생성
        if (_request_message.getHttpMethod() == "HEAD")
            message_body = "";
        response_message = getResponseMessage(status, message_body);
        //response_message = getResponseMessage(status, message_body, cgi_header);
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
    catch(const std::exception& e)
    {
        response_message = getErrorResponse(500);
    }
    return (response_message);
}
