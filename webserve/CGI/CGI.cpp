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
    this->_env["HTTP_ACCEPT"] = headers["Accept"];
    this->_env["HTTP_ACCEPT_CHARSET"] = headers["Accept-CH"];
    this->_env["HTTP_ACCEPT_ENCODING"] = headers["Accept-Encoding"]; // 여러개 일땐?
    this->_env["HTTP_ACCEPT_LANGUAGE"] = headers["Accept-Language"];
    this->_env["HTTP_FORWARDED"] = headers["Forwarded"];
    this->_env["HTTP_HOST"] = headers["Host"];
    this->_env["HTTP_PROXY_AUTHORIZATION"] = headers["Proxy-Authorization"];
    this->_env["HTTP_USER_AGENT"] = headers["User-Agent"];
    this->_env["PATH_INFO"] = headers["Accept-Encoding"]; // ?
    this->_env["PATH_TRANSLATED"] = headers["Accept-Encoding"]; // ?
    this->_env["QUERY_STRING"] = headers["Accept-Encoding"];
    this->_env["REMOTE_ADDR"] = headers["Accept-Encoding"];
    this->_env["REMOTE_HOST"] = headers["Accept-Encoding"];
    this->_env["REMOTE_USER"] = headers["Accept-Encoding"];
    this->_env["REQUEST_METHOD"] = headers["Accept-Encoding"];
    this->_env["SCRIPT_NAME"] = headers["Accept-Encoding"];
    this->_env["SERVER_NAME"] = headers["Accept-Encoding"];
    this->_env["SERVER_PORT"] = headers["Accept-Encoding"];
    this->_env["SERVER_PROTOCOL"] = headers["Accept-Encoding"];
    this->_env["SERVER_SOFTWARE"] = "webserv/1.0";
    this->_env["HTTP_COOKIE"] = headers["Accept-Encoding"];
    this->_env["WEBTOP_USER"] = headers["Accept-Encoding"];
    this->_env["NCHOME"] = headers["Accept-Encoding"];
}

char **CGI::getEnvChar(void) const
{
    char    **res = new char*[this->_env.size() + 1];
    int     i = 0;

    std::map<std::string, std::string>::const_iterator iter = this->_env.begin();
    for (; iter != this->_env.end(); iter++)
    {
        std::string temp = iter->first + "=" + iter->second;
        res[i] = new char[temp.size() + 1];
        res[i] = strcpy(res[i], temp.c_str());
        i++;
    }
    res[i] = NULL;
    return (res);
}

std::string CGI::excute(std::string scriptName)
{
    std::string result = "";
    int         fd[2];
    int         std_fd[2];
    pid_t       pid;
    char        **env;

    if (pipe(fd) < 0)
    {
        std::cerr << "pipe error\n";
        exit(1);
    }

    if (pid = fork() < 0)
    {
        std::cerr << "fork error\n";
        exit(1);
    }

    std_fd[READ] = dup(STDIN_FILENO);
    std_fd[WRITE] = dup(STDOUT_FILENO);

    dup2(fd[READ], STDIN_FILENO);
    dup2(fd[WRITE], STDOUT_FILENO);

    if (pid == 0)
    {
        close(fd[READ]);
        char * const * null = NULL;
        try
        {
            env = this->getEnvChar();
        }
        catch (std::bad_alloc &e)
        {
            std::cerr << e.what() << std::endl;
        }
        
        execve(scriptName.c_str(), null, env);
        std::cerr << "execve error\n";
    }
    else
    {
        char buf[1000] = {0, };
        int ret = 1;

        waitpid(-1, NULL, 0);

        close(fd[WRITE]);
        while (ret > 0)
        {
            memset(buf, 0, 1000);
            ret = read(fd[READ], buf, 1000);
            result += buf;
        }
    }

    dup2(STDIN_FILENO, std_fd[READ]);
    dup2(STDOUT_FILENO, std_fd[WRITE]);

    close(fd[READ]);
    close(fd[WRITE]);

    close(std_fd[READ]);
    close(std_fd[WRITE]);

    for (int i = 0; env[i] != NULL; i++)
    {
        delete env[i];
    }
    delete[] env;

    if (pid == 0)
        exit(0);

    return (result);
}
