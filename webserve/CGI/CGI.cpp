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
    this->_block = obj._block;
    this->_request_message = obj._request_message;
    this->_env = obj._env;
    return *this;
}

CGI::~CGI(void) {}


CGI::CGI(LocationBlock *block, HttpRequestMessage request_message)
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

    this->_block = block;
    this->_request_message = request_message;
}

void CGI::setEnv(void)
{
    std::map<std::string, std::string> headers = _request_message.getHeaders();

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

    this->_env["PATH_INFO"] = _request_message.getPathInfo(); // ?
    this->_env["PATH_TRANSLATED"] = _request_message.getPathTranslate(); // ?
    this->_env["QUERY_STRING"] = _request_message.getQueryString();
    
    std::string client_ip = ft::splitString(headers["X-Forwarded-For"], " ")[0];
    if (client_ip[client_ip.length() - 1] == ',')
        client_ip = client_ip.substr(0, client_ip.length() - 1);
    this->_env["REMOTE_ADDR"] = client_ip;
    this->_env["REMOTE_HOST"] = client_ip;
    this->_env["REMOTE_USER"] = headers["Authorization"];
    this->_env["REQUEST_METHOD"] = _request_message.getHttpMethod();
    this->_env["SCRIPT_NAME"] = _request_message.getPathInfo();

    if (headers.find("Host") != headers.end())
        this->_env["SERVER_NAME"] = headers["Host"];
    else
        this->_env["SERVER_NAME"] = this->_env["REMOTE_ADDR"];

    this->_env["SERVER_PORT"] = _block->getPort(); 
    this->_env["SERVER_PROTOCOL"] = _request_message.getHttpVersion(); 
    this->_env["SERVER_SOFTWARE"] = "webserv/1.0";


    this->_env["HTTP_COOKIE"] = "";
    this->_env["WEBTOP_USER"] = "";
    this->_env["NCHOME"] = "";
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
    char        **env = NULL;

    setEnv();
    if (pipe(fd) < 0)
    {
        std::cerr << "pipe error\n";
        exit(1);
    }

    if ((pid = fork()) < 0)
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
        //int ret = 1;

        waitpid(-1, NULL, 0);

        close(fd[WRITE]);
        while (read(fd[READ], buf, 1000) > 0)
        {
            memset(buf, 0, 1000);
            //ret = read(fd[READ], buf, 1000);
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
