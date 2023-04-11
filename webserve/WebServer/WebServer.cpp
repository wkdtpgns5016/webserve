#include "WebServer.hpp"
#include <fstream>
#include <sstream>

std::string	read_file_into_string(std::string filename)
{
    std::ifstream f(filename);
    std::string str;

    if (!f.good() || !f.is_open())
	{
		std::cout << "Error: Do not stream open of file open." << std::endl;
		return (str);
	}

    if(f)
    {
        std::ostringstream ss;
        ss << f.rdbuf();
        str = ss.str();
    }
    return str;
}

WebServer::WebServer()
{
}

WebServer::WebServer(std::string path)
{
    std::string config = read_file_into_string(path);
    std::vector<std::string> sBlocks = ft::splitBlockString(config);

    for (unsigned int i = 0; i < sBlocks.size(); i++)
    {
        _servers.push_back(Server(sBlocks[i]));
        std::cout << sBlocks[i] << std::endl;
    }
}

void WebServer::run(void)
{
    std::list<Server>::iterator iter = _servers.begin();
    for (; iter != _servers.end(); iter++)
    {
        (*iter).threading();
    }
    iter = _servers.begin();
    for (; iter != _servers.end(); iter++)
    {
        pthread_t tmp = (*iter).getThread();
        pthread_join(tmp, NULL);
    }
}
