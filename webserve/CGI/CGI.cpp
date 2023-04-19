#include "CGI.hpp"

CGI::CGI(void)
{
    this->_env.insert(std::make_pair("AUTH_TYPE", ""));
    this->_env.insert(std::make_pair("CONTENT_LENGTH", ""));
    this->_env.insert(std::make_pair("CONTENT_TYPE", ""));
    this->_env.insert(std::make_pair("GATEWAY_INTERFACE", ""));
    this->_env.insert(std::make_pair("HTTP_ACCEPT", ""));
    this->_env.insert(std::make_pair("HTTP_ACCEPT_CHARSET", ""));
    this->_env.insert(std::make_pair("HTTP_ACCEPT_ENCODING", ""));
    this->_env.insert(std::make_pair("HTTP_ACCEPT_LANGUAGE", ""));
    this->_env.insert(std::make_pair("HTTP_FORWARDED", ""));
    this->_env.insert(std::make_pair("HTTP_HOST", ""));
    this->_env.insert(std::make_pair("HTTP_PROXY_AUTHORIZATION", ""));
    this->_env.insert(std::make_pair("HTTP_USER_AGENT", ""));
    this->_env.insert(std::make_pair("PATH_INFO", ""));
    this->_env.insert(std::make_pair("PATH_TRANSLATED", ""));
    this->_env.insert(std::make_pair("QUERY_STRING", ""));
    this->_env.insert(std::make_pair("REMOTE_ADDR", ""));
    this->_env.insert(std::make_pair("REMOTE_HOST", ""));
    this->_env.insert(std::make_pair("REMOTE_USER", ""));
    this->_env.insert(std::make_pair("REQUEST_METHOD", ""));
    this->_env.insert(std::make_pair("SCRIPT_NAME", ""));
    this->_env.insert(std::make_pair("SERVER_NAME", ""));
    this->_env.insert(std::make_pair("SERVER_PORT", ""));
    this->_env.insert(std::make_pair("SERVER_PROTOCOL", ""));
    this->_env.insert(std::make_pair("SERVER_SOFTWARE", ""));
    this->_env.insert(std::make_pair("HTTP_COOKIE", ""));
    this->_env.insert(std::make_pair("WEBTOP_USER", ""));
    this->_env.insert(std::make_pair("NCHOME", ""));
}

CGI::CGI(const CGI &obj)
{
    *this = obj;
}

CGI CGI::operator=(const CGI &obj)
{
    this->_s_parser = obj._s_parser;
    this->_l_parser = obj._l_parser;
    this->_s_handler = obj._s_handler;
    this->_env = obj._env;
}

CGI::~CGI(void) {}


CGI::CGI(ServerParser s_parser, LocationParser l_parser, ServerHandler s_handler)
{
    this->_env.insert(std::make_pair("AUTH_TYPE", ""));
    this->_env.insert(std::make_pair("CONTENT_LENGTH", ""));
    this->_env.insert(std::make_pair("CONTENT_TYPE", ""));
    this->_env.insert(std::make_pair("GATEWAY_INTERFACE", ""));
    this->_env.insert(std::make_pair("HTTP_ACCEPT", ""));
    this->_env.insert(std::make_pair("HTTP_ACCEPT_CHARSET", ""));
    this->_env.insert(std::make_pair("HTTP_ACCEPT_ENCODING", ""));
    this->_env.insert(std::make_pair("HTTP_ACCEPT_LANGUAGE", ""));
    this->_env.insert(std::make_pair("HTTP_FORWARDED", ""));
    this->_env.insert(std::make_pair("HTTP_HOST", ""));
    this->_env.insert(std::make_pair("HTTP_PROXY_AUTHORIZATION", ""));
    this->_env.insert(std::make_pair("HTTP_USER_AGENT", ""));
    this->_env.insert(std::make_pair("PATH_INFO", ""));
    this->_env.insert(std::make_pair("PATH_TRANSLATED", ""));
    this->_env.insert(std::make_pair("QUERY_STRING", ""));
    this->_env.insert(std::make_pair("REMOTE_ADDR", ""));
    this->_env.insert(std::make_pair("REMOTE_HOST", ""));
    this->_env.insert(std::make_pair("REMOTE_USER", ""));
    this->_env.insert(std::make_pair("REQUEST_METHOD", ""));
    this->_env.insert(std::make_pair("SCRIPT_NAME", ""));
    this->_env.insert(std::make_pair("SERVER_NAME", ""));
    this->_env.insert(std::make_pair("SERVER_PORT", ""));
    this->_env.insert(std::make_pair("SERVER_PROTOCOL", ""));
    this->_env.insert(std::make_pair("SERVER_SOFTWARE", ""));
    this->_env.insert(std::make_pair("HTTP_COOKIE", ""));
    this->_env.insert(std::make_pair("WEBTOP_USER", ""));
    this->_env.insert(std::make_pair("NCHOME", ""));

    this->_s_parser = s_parser;
    this->_l_parser = l_parser;
    this->_s_handler = s_handler;
}

void CGI::setEnv(void)
{
    std::map<std::string, std::string> headers = _s_handler.getRequestMessage().getHeaders();

    this->_env["AUTH_TYPE"] = ft::splitString(headers["Authorization"], " ")[0];
    this->_env["CONTENT_LENGTH"] = headers["Content-Length"];
    this->_env["CONTENT_TYPE"] = headers["Content-Type"];
    this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
    this->_env["HTTP_ACCEPT"] = "";
    this->_env["HTTP_ACCEPT_CHARSET"] = "";
    this->_env["HTTP_ACCEPT_ENCODING"] = "";
    this->_env["HTTP_ACCEPT_LANGUAGE"] = "";
    this->_env["HTTP_FORWARDED"] = "";
    this->_env["HTTP_HOST"] = "";
    this->_env["HTTP_PROXY_AUTHORIZATION"] = "";
    this->_env["HTTP_USER_AGENT"] = "";
    this->_env["PATH_INFO"] = "";
    this->_env["PATH_TRANSLATED"] = "";
    this->_env["QUERY_STRING"] = "";
    this->_env["REMOTE_ADDR"] = "";
    this->_env["REMOTE_HOST"] = "";
    this->_env["REMOTE_USER"] = "";
    this->_env["REQUEST_METHOD"] = "";
    this->_env["SCRIPT_NAME"] = "";
    this->_env["SERVER_NAME"] = "";
    this->_env["SERVER_PORT"] = "";
    this->_env["SERVER_PROTOCOL"] = "";
    this->_env["SERVER_SOFTWARE"] = "webserv/1.0";
    this->_env["HTTP_COOKIE"] = "";
    this->_env["WEBTOP_USER"] = "";
    this->_env["NCHOME"] = "";
}

void CGI::excute(void)
{

}
