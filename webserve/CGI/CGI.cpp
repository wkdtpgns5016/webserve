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
    this->_env.insert(std::make_pair("REQUEST_URI", ""));
    this->_env.insert(std::make_pair("SCRIPT_FILENAME", ""));
    this->_env.insert(std::make_pair("SCRIPT_NAME", ""));
    this->_env.insert(std::make_pair("SERVER_NAME", ""));
    this->_env.insert(std::make_pair("SERVER_PORT", ""));
    this->_env.insert(std::make_pair("SERVER_PROTOCOL", ""));
    this->_env.insert(std::make_pair("SERVER_SOFTWARE", ""));
    this->_env.insert(std::make_pair("HTTP_COOKIE", ""));
    this->_env.insert(std::make_pair("WEBTOP_USER", ""));
    this->_env.insert(std::make_pair("NCHOME", ""));
    this->_env.insert(std::make_pair("REDIRECT_STATUS", ""));

    this->_block = block;
    this->_request_message = request_message;
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
    this->_env["HTTP_ACCEPT"] = headers["Accept"];
    this->_env["HTTP_ACCEPT_CHARSET"] = headers["Accept-CH"];
    this->_env["HTTP_ACCEPT_ENCODING"] = headers["Accept-Encoding"]; // 여러개 일땐?
    this->_env["HTTP_ACCEPT_LANGUAGE"] = headers["Accept-Language"];
    this->_env["HTTP_FORWARDED"] = headers["Forwarded"];
    this->_env["HTTP_HOST"] = headers["Host"];
    this->_env["HTTP_PROXY_AUTHORIZATION"] = headers["Proxy-Authorization"];
    this->_env["HTTP_USER_AGENT"] = headers["User-Agent"];

    this->_env["PATH_INFO"] = _block->getRoot() + _request_message.getPathInfo(); // ?
    this->_env["PATH_TRANSLATED"] = "/Users/sehjang/webserve";// ?
    this->_env["QUERY_STRING"] = _request_message.getQueryString();
    
    std::string client_ip = "";
    if (headers.find("X-Forwarded-For") != headers.end())
        client_ip = ft::splitString(headers["X-Forwarded-For"], " ")[0];
    if (client_ip[client_ip.length() - 1] == ',')
        client_ip = client_ip.substr(0, client_ip.length() - 1);

    this->_env["REMOTE_ADDR"] = "127.0.0.1";
    this->_env["REMOTE_HOST"] = client_ip;
    this->_env["REMOTE_USER"] = headers["Authorization"];
    this->_env["REQUEST_METHOD"] = _request_message.getHttpMethod();
    this->_env["SCRIPT_FILENAME"] = this->_env["PATH_INFO"];
    this->_env["SCRIPT_NAME"] = this->_env["PATH_INFO"];
    this->_env["REQUEST_URI"] = "/" + this->_env["SCRIPT_NAME"];

    if (headers.find("Host") != headers.end())
        this->_env["SERVER_NAME"] = headers["Host"];
    else
        this->_env["SERVER_NAME"] = this->_env["REMOTE_ADDR"];

    this->_env["SERVER_PORT"] = ft::itos(_block->getPort()); 
    this->_env["SERVER_PROTOCOL"] = _request_message.getHttpVersion(); 
    this->_env["SERVER_SOFTWARE"] = "webserv/1.0";
    this->_env["REDIRECT_STATUS"] = "CGI";


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
    //int         fd[2];
    //int         std_fd[2];
    pid_t       pid;
    char        **env = NULL;

    int saveStdin = dup(STDIN_FILENO);
    int saveStdout = dup(STDOUT_FILENO);


    setEnv();


    std::vector<std::string> arr = ft::splitString(scriptName, " ");
    const char *arg[] = { arr[0].c_str(), arr.size() > 1 ? arr[1].c_str() : NULL , NULL };
    // if (pipe(fd) < 0)
    // {
    //     std::cerr << "pipe error\n";
    //     exit(1);
    // }

    FILE    *fIn = tmpfile();
	FILE	*fOut = tmpfile();
	long	fdIn = fileno(fIn);
	long	fdOut = fileno(fOut);
	int		ret = 1;
    std::string _body = _request_message.getMessageBody();
	write(fdIn, _body.c_str(), _body.size());
	lseek(fdIn, 0, SEEK_SET);

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
		std::cerr << "Fork crashed." << std::endl;
		return ("Status: 500\r\n\r\n");
	}
	else if (!pid)
	{
		//char * const * nll = NULL;
		dup2(fdIn, STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		execve(arr[0].c_str(), (char * const *)arg, env);
		std::cerr << "Execve crashed." << std::endl;
		write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);
	}
	else
	{
		char	buffer[1024] = {0};
		waitpid(-1, NULL, 0);
		lseek(fdOut, 0, SEEK_SET);
		ret = 1;
		while (ret > 0)
		{
			memset(buffer, 0, 1024);
			ret = read(fdOut, buffer, 1024 - 1);
			result += buffer;
		}
	}
	dup2(saveStdin, STDIN_FILENO);
	dup2(saveStdout, STDOUT_FILENO);
	fclose(fIn);
	fclose(fOut);
	close(fdIn);
	close(fdOut);
	close(saveStdin);
	close(saveStdout);
	for (size_t i = 0; env[i]; i++)
		delete[] env[i];
	delete[] env;
	if (!pid)
		exit(0);
	return (result);
}
