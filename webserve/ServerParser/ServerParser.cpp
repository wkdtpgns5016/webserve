#include "ServerParser.hpp"

ServerParser::ServerParser(const std::string block_script)
{
}

ServerParser::~ServerParser()
{
}

int	ServerParser::getPort() const
{
	return _port;
}
std::string	ServerParser::getAddr() const
{
	return _addr;
}

std::string	ServerParser::getServerName() const
{
	return _server_name;
}

std::string	ServerParser::getIndex() const
{
	return _index;
}

std::string	ServerParser::getDefaultErrorPaget() const
{
	return _default_error_page;
}

int	ServerParser::getClientBodySize() const
{
	return _client_body_size;
}

//std::string	ServerParser::getLocations() const
//{
//	return _locations;
//}

