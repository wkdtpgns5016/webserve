#include "ServerParser.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <locale>
#include <sys/_types/_size_t.h>

ServerParser::ServerParser()
{
}

ServerParser::ServerParser(const ServerParser& parser)
{
    _port = parser._port;
    _addr = parser._addr;
    _client_body_size = parser._client_body_size;
    _server_name = parser._server_name;
    _index = parser._index;
    _default_error_page = parser._default_error_page;
}

ServerParser &ServerParser::operator=(const ServerParser& obj)
{
    _port = obj._port;
    _addr = obj._addr;
    _client_body_size = obj._client_body_size;
    _server_name = obj._server_name;
    _index = obj._index;
    _default_error_page = obj._default_error_page;
    return (*this);
}

ServerParser::ServerParser(const std::string& script)
{
	size_t	pos = jumpTrash(script, 1);
	size_t	element_end = 0;
	size_t	block_id_end = 0;

	setParsingFunctionArray();
	while (pos != std::string::npos
			&& pos + 1 < script.length())
	{
		element_end = jumpElement(script, pos);
		block_id_end = jumpBlockId(script, pos);
		if (element_end < block_id_end)
			pos += parseElement(script.substr(pos, element_end - pos));
		else
			pos += parseBlock(script.substr(pos, jumpBlock(script, block_id_end) - pos));
	}
}

size_t	ServerParser::parseElement(const std::string& script)
{
	const std::string	element_id[7] = {"listen", "root", "server_name", "index", "error_page", "client_max_body_size", ""};
	
	std::pair<std::string, std::string>	id_value_pair = divideElementIdAndValue(script, 0);
	int i = 0;
	for (; i < 6; i++)
		if (id_value_pair.first == element_id[i])
			break;
	(this->*_parsing_func[i])(id_value_pair.second);
	return script.length();
}

size_t	ServerParser::parseBlock(const std::string& script)
{
	_blocks.push_back(script);

	return script.length();
}

void	ServerParser::setParsingFunctionArray()
{
	_parsing_func[0] = &ServerParser::parsePort;
	_parsing_func[1] = &ServerParser::parseRoot;
	_parsing_func[2] = &ServerParser::parseServerName;
	_parsing_func[3] = &ServerParser::parseIndex;
	_parsing_func[4] = &ServerParser::parseDefaultErrorPage;
	_parsing_func[5] = &ServerParser::parseClientBodySize;
	_parsing_func[6] = &ServerParser::parseNoMatchId;
}

void	ServerParser::parsePort(const std::string& value)
{
	_port = std::strtol(value.c_str(), NULL, 10);
}

void	ServerParser::parseRoot(const std::string& value)
{
	_root = value;
}

void	ServerParser::parseServerName(const std::string& value)
{
	_server_name = value;
}

void	ServerParser::parseIndex(const std::string& value)
{
	_index = value;
}

void	ServerParser::parseDefaultErrorPage(const std::string& value)
{
	_default_error_page = value;
}

void	ServerParser::parseClientBodySize(const std::string& value)
{
	_client_body_size = std::strtol(value.c_str(), NULL, 10);
}

void	ServerParser::parseNoMatchId(const std::string& value)
{
	if (value.empty() || 1)
		throw std::exception();
}

ServerParser::~ServerParser() { }
int	ServerParser::getPort() const { return _port; }
std::string	ServerParser::getRoot() const { return _root; }
std::string	ServerParser::getAddr() const { return _addr; }
std::string	ServerParser::getServerName() const { return _server_name; }
std::string	ServerParser::getIndex() const { return _index; }
std::string	ServerParser::getDefaultErrorPaget() const { return _default_error_page; }
int	ServerParser::getClientBodySize() const { return _client_body_size; }
std::vector<std::string>	ServerParser::getLocations() const { return _blocks; }
