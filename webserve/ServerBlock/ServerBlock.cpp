#include "ServerBlock.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <locale>
#include <sys/_types/_size_t.h>

ServerBlock::ServerBlock() : Block()
{
}

ServerBlock::ServerBlock(const ServerBlock& block) : Block()
{
    _port = block._port;
    _addr = block._addr;
    _client_body_size = block._client_body_size;
    _server_name = block._server_name;
    _index = block._index;
    _default_error_page = block._default_error_page;
}

ServerBlock &ServerBlock::operator=(const ServerBlock& obj)
{
    _port = obj._port;
    _addr = obj._addr;
    _client_body_size = obj._client_body_size;
    _server_name = obj._server_name;
    _index = obj._index;
    _default_error_page = obj._default_error_page;
    return (*this);
}

ServerBlock::ServerBlock(const std::string& script) : Block()
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

size_t	ServerBlock::parseElement(const std::string& script)
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

size_t	ServerBlock::parseBlock(const std::string& script)
{
	_blocks.push_back(script);

	return script.length();
}

void	ServerBlock::setParsingFunctionArray()
{
	_parsing_func[0] = &ServerBlock::parsePort;
	_parsing_func[1] = &ServerBlock::parseRoot;
	_parsing_func[2] = &ServerBlock::parseServerName;
	_parsing_func[3] = &ServerBlock::parseIndex;
	_parsing_func[4] = &ServerBlock::parseDefaultErrorPage;
	_parsing_func[5] = &ServerBlock::parseClientBodySize;
	_parsing_func[6] = &ServerBlock::parseNoMatchId;
}

void	ServerBlock::parsePort(const std::string& value)
{
	_port = std::strtol(value.c_str(), NULL, 10);
}

void	ServerBlock::parseRoot(const std::string& value)
{
	_root = value;
}

void	ServerBlock::parseServerName(const std::string& value)
{
	_server_name = value;
}

void	ServerBlock::parseIndex(const std::string& value)
{
	_index = value;
}

void	ServerBlock::parseDefaultErrorPage(const std::string& value)
{
	_default_error_page = value;
}

void	ServerBlock::parseClientBodySize(const std::string& value)
{
	_client_body_size = std::strtol(value.c_str(), NULL, 10);
}

void	ServerBlock::parseNoMatchId(const std::string& value)
{
	if (value.empty() || 1)
		throw std::exception();
}

ServerBlock::~ServerBlock() { }
int	ServerBlock::getPort() const { return _port; }
std::string	ServerBlock::getRoot() const { return _root; }
std::string	ServerBlock::getAddr() const { return _addr; }
std::string	ServerBlock::getServerName() const { return _server_name; }
std::string	ServerBlock::getIndex() const { return _index; }
std::string	ServerBlock::getDefaultErrorPaget() const { return _default_error_page; }
int	ServerBlock::getClientBodySize() const { return _client_body_size; }
std::vector<std::string>	ServerBlock::getLocations() const { return _blocks; }
