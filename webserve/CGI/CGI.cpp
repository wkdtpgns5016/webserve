#include "CGI.hpp"

CGI::CGI(void)
{
    initEnv();
}

CGI::CGI(const CGI &obj)
{
    *this = obj;
}

CGI CGI::operator=(const CGI &obj)
{
    this->_config = obj._config;
    this->_request_message = obj._request_message;
    this->_env = obj._env;
    return *this;
}

CGI::~CGI(void) {}


CGI::CGI(ConfigDto config, HttpRequestMessage request_message)
{
    initEnv();
    this->_config = config;
    this->_request_message = request_message;
}

void CGI::initEnv(void)
{
    this->_env.insert(std::make_pair("AUTH_TYPE", ""));
    this->_env.insert(std::make_pair("CONTENT_LENGTH", ""));
    this->_env.insert(std::make_pair("CONTENT_TYPE", ""));
    this->_env.insert(std::make_pair("GATEWAY_INTERFACE", ""));
    this->_env.insert(std::make_pair("PATH_INFO", ""));
    this->_env.insert(std::make_pair("PATH_TRANSLATED", ""));
    this->_env.insert(std::make_pair("QUERY_STRING", ""));
    this->_env.insert(std::make_pair("REMOTE_ADDR", ""));
    this->_env.insert(std::make_pair("REMOTE_IDENT", ""));
    this->_env.insert(std::make_pair("REMOTE_USER", ""));
    this->_env.insert(std::make_pair("REQUEST_METHOD", ""));
    this->_env.insert(std::make_pair("REQUEST_URI", ""));
    this->_env.insert(std::make_pair("SCRIPT_FILENAME", ""));
    this->_env.insert(std::make_pair("SCRIPT_NAME", ""));
    this->_env.insert(std::make_pair("SERVER_NAME", ""));
    this->_env.insert(std::make_pair("SERVER_PORT", ""));
    this->_env.insert(std::make_pair("SERVER_PROTOCOL", ""));
    this->_env.insert(std::make_pair("SERVER_SOFTWARE", ""));
    this->_env.insert(std::make_pair("REDIRECT_STATUS", ""));
    this->_env.insert(std::make_pair("HTTP_X_SECRET_HEADER_FOR_TEST", ""));
    this->_env.insert(std::make_pair("HTTP_X_UPLOAD_FILE_PATH", ""));
}

void CGI::setEnv(void)
{
    std::map<std::string, std::string> headers = _request_message.getHeaders();

    if (headers.find("Authorization") != headers.end())
        this->_env["AUTH_TYPE"] = ft::splitString(headers["Authorization"], " ")[0];
    else
        this->_env["AUTH_TYPE"] = "";
    this->_env["CONTENT_LENGTH"] = headers["Content-Length"];
    this->_env["CONTENT_TYPE"] = headers["Content-Type"];
    this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
    this->_env["PATH_INFO"] = _config.getRoot() + _request_message.getPathInfo(); // ?
    this->_env["PATH_TRANSLATED"] = "/Users/pjang/Common-Circle/webserve";// ?
    this->_env["QUERY_STRING"] = _request_message.getQueryString();
    
    std::string client_ip = "";
    if (headers.find("X-Forwarded-For") != headers.end())
        client_ip = ft::splitString(headers["X-Forwarded-For"], " ")[0];
    if (client_ip[client_ip.length() - 1] == ',')
        client_ip = client_ip.substr(0, client_ip.length() - 1);

    this->_env["REMOTE_ADDR"] = "127.0.0.1";
    this->_env["REMOTE_IDENT"] = headers["Authorization"];
    this->_env["REMOTE_USER"] = headers["Authorization"];
    this->_env["REQUEST_METHOD"] = _request_message.getHttpMethod();
    this->_env["SCRIPT_FILENAME"] = this->_env["PATH_INFO"];
    this->_env["SCRIPT_NAME"] = this->_env["PATH_INFO"];
    this->_env["REQUEST_URI"] = this->_env["SCRIPT_NAME"];

    if (headers.find("Host") != headers.end())
        this->_env["SERVER_NAME"] = headers["Host"];
    else
        this->_env["SERVER_NAME"] = this->_env["REMOTE_ADDR"];

    this->_env["SERVER_PORT"] = ft::itos(_config.getPort()); 
    this->_env["SERVER_PROTOCOL"] = _request_message.getHttpVersion(); 
    this->_env["SERVER_SOFTWARE"] = "webserv/1.0";
    this->_env["REDIRECT_STATUS"] = "CGI";
    this->_env["HTTP_X_SECRET_HEADER_FOR_TEST"] = headers["X-Secret-Header-For-Test"];
    this->_env["HTTP_X_UPLOAD_FILE_PATH"] = _config.getUploadPath();
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

int ft_strlen(const char* str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;
    return (len);
}

void test(int fd, std::string body)
{
    int ret = 1;
    size_t idx = 0;
    while (idx < body.size())
    {
        ret = write(fd, body.substr(idx, 1000).c_str(), ft_strlen(body.substr(idx, 1000).c_str()));
        if (ret == -1)
            continue ;
        idx += 1000;
    }
}

std::string CGI::excute(std::string scriptName)
{
    std::string result = "";
    //int         fd[2];
    //int         std_fd[2];
    pid_t       pid;
    char        **env = NULL;

    int saveStdin = dup(STDIN_FILENO);
    int saveStdout = dup(STDOUT_FILENO);


    setEnv();


    std::vector<std::string> arr = ft::splitString(scriptName, " ");
    const char *arg[] = { arr[0].c_str(), arr.size() > 1 ? arr[1].c_str() : NULL , NULL };
    int     fd_in[2];
    int     fd_out[2];
    if (pipe(fd_in) < 0)
    {
        Logger::writeErrorLog("Pipe crashed");
		return ("Status: 500\r\n\r\n");
    }
    if (pipe(fd_out) < 0)
    {
        Logger::writeErrorLog("Pipe crashed");
		return ("Status: 500\r\n\r\n");
    }

    if (fcntl(fd_in[READ], F_SETFL,  O_NONBLOCK) < 0)
    {
        Logger::writeErrorLog("Non-blocking crashed");
		return ("Status: 500\r\n\r\n");
    }

    // if (fcntl(fd_in[WRITE], F_SETFL,  O_NONBLOCK) < 0)
    // {
    //     Logger::writeErrorLog("Non-blocking crashed");
	// 	return ("Status: 500\r\n\r\n");
    // }

    if (fcntl(fd_out[READ], F_SETFL,  O_NONBLOCK) < 0)
    {
        Logger::writeErrorLog("Non-blocking crashed");
		return ("Status: 500\r\n\r\n");
    }

    if (fcntl(fd_out[WRITE], F_SETFL,  O_NONBLOCK) < 0)
    {
        Logger::writeErrorLog("Non-blocking crashed");
		return ("Status: 500\r\n\r\n");
    }

	int		ret = 1;
    std::string _body = _request_message.getMessageBody();

    // size_t idx = 0;
    // while (idx < _body.size())
    // {
    //     ret = write(fd_in[WRITE], _body.substr(idx, 300000).c_str(), ft_strlen(_body.substr(idx, 300000).c_str()));
    //     if (ret == -1)
    //         continue ;
    //     idx += 300000;
    // }
    write(fd_in[WRITE], _body.c_str(), _body.size());
    // test(fd_in[WRITE], _body);
    close(fd_in[WRITE]);

    // fcntl(fd_in[WRITE], F_SETFL, O_NONBLOCK);

    try
    {
        env = this->getEnvChar();
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << e.what() << std::endl;
    }

	pid = fork();
	if (pid == -1)
	{
        Logger::writeErrorLog("Fork crashed");
		return ("Status: 500\r\n\r\n");
	}
	else if (!pid)
	{
		//char * const * nll = NULL;

        dup2(fd_in[READ], STDIN_FILENO);
        dup2(fd_out[WRITE], STDOUT_FILENO);

        close(fd_in[READ]);
        // close(fd_in[WRITE]);
        // close(fd_out[READ]);
        // close(fd_out[WRITE]);

        // (void)arr;
        // (void)arg;
        // (void)env;
		execve(arr[0].c_str(), (char * const *)arg, env);
        Logger::writeErrorLog("Execve crashed");
		write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);

        // close(fd_in[READ]);
        // close(fd_in[WRITE]);
        // close(fd_out[READ]);
        // close(fd_out[WRITE]);
	}
	else
	{
		char	buffer[1024] = {0};
		waitpid(-1, NULL, 0);

        close(fd_in[READ]);
        // close(fd_in[WRITE]);
        close(fd_out[WRITE]);

        ret = 1;
		while (ret > 0)
		{
			memset(buffer, 0, 1024);
			ret = read(fd_out[READ], buffer, 1024 - 1);
			result += buffer;
		}

        close(fd_out[READ]);
	}
	dup2(saveStdin, STDIN_FILENO);
	dup2(saveStdout, STDOUT_FILENO);
	close(saveStdin);
	close(saveStdout);
    // close(fd_in[READ]);
    // close(fd_in[WRITE]);
	for (size_t i = 0; env[i]; i++)
		delete[] env[i];
	delete[] env;
	if (!pid)
		exit(0);
	return (result);
}
