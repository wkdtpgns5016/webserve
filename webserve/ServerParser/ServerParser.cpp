#include "ServerParser.hpp"
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <locale>

ServerParser::ServerParser()
{
    _port = 80;
    _addr = "";
    _client_body_size = 0;
    _server_name = "";
    _index = "";
    _default_error_page = "";
}

ServerParser::~ServerParser() { }
int	ServerParser::getPort() const { return _port; }
std::string	ServerParser::getAddr() const { return _addr; }
std::string	ServerParser::getServerName() const { return _server_name; }
std::string	ServerParser::getIndex() const { return _index; }
std::string	ServerParser::getDefaultErrorPaget() const { return _default_error_page; }
int	ServerParser::getClientBodySize() const { return _client_body_size; }
//std::string	ServerParser::getLocations() const { return _locations; }

ServerParser::ServerParser(const std::string& server_block)
{
	std::string	server_block_cpy = server_block;

	_port = 80;
    _addr = "";
    _client_body_size = 0;
    _server_name = "";
    _index = "";
    _default_error_page = "";

	parseServerBrace(&server_block_cpy);
	parseLocationBlock(&server_block_cpy);
	parseServerBlock(server_block_cpy);
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

void	ServerParser::parseServerBrace(std::string* script)
{
	if (script->compare(0, 10, "server\n{\n") == 0)
		return ; //throw
	script->erase(0, 10);

	size_t	last_brace_pos = script->find_last_of('}');
	if (script->compare(last_brace_pos - 1, 3, "\n}\n") == 0)
		return; //throw
	script->erase(last_brace_pos - 1, 3);
}

void	ServerParser::parseLocationBlock(std::string* script) //location parser에 location블록을 넘겨주고, script에서 삭제
{
	(void)script;
	//ft::splitString(*script);
	//deleteLocationBlock();
}

void	ServerParser::removeFirstWhiteSpaces(std::vector<std::string> *block_lines)
{
	std::vector<std::string>::iterator ite = block_lines->end();

	for (std::vector<std::string>::iterator it = block_lines->begin(); it != ite; it++)
	{
		std::string	line = *it;
		size_t		line_length = line.size();
		size_t		space_end = 0;

		for (; space_end < line_length ; space_end++)
			if(std::isspace(line[space_end], std::locale()) == false)
				break;

		it->erase(0, space_end);
		if (it->empty())
			block_lines->erase(it);
	}
}

bool	ServerParser::checkIdentifier(const std::string& line, const std::string& identifier)
{
	size_t	id_length = identifier.length();

	if (line.compare(0, id_length, identifier) == 0
			&& line.size() > id_length
			&& std::isspace(line.at(id_length), std::locale()) == true)
		return true;
	return false;
}


std::vector<std::string>	ServerParser::extractContents(std::string line)
{
	std::vector<std::string> ret = ft::splitString(line, " ");

	ret.erase(ret.begin());
	return ret;
}

void	ServerParser::loopForParsing(std::vector<std::string>* block_lines, const std::string& keyword, bool (ServerParser::*parseFuntion)(std::vector<std::string>))
{
	std::vector<std::string>::iterator ite = block_lines->end();
	
	for (std::vector<std::string>::iterator it = block_lines->begin(); it != ite; it++)
	{
		if (checkIdentifier(*it, keyword)
				&& (this->*parseFuntion)(extractContents(*it)))
			block_lines->erase(it);
	}
}
void	ServerParser::parseServerBlock(const std::string& server_block)
{
	std::vector<std::string> block_lines = ft::splitString(server_block, ";");

	removeFirstWhiteSpaces(&block_lines);
	loopForParsing(&block_lines, "listen", &ServerParser::parsePort);
	loopForParsing(&block_lines, "root", &ServerParser::parseAddr);
	loopForParsing(&block_lines, "server_name", &ServerParser::parseServerName);
	loopForParsing(&block_lines, "index", &ServerParser::parseIndex);
	loopForParsing(&block_lines, "error_page", &ServerParser::parseDefaultErrorPage);
	loopForParsing(&block_lines, "client_max_body_size", &ServerParser::parseClientBodySize);


}

bool	ServerParser::parsePort(std::vector<std::string> contents)
{
	if (contents.size() != 1)
		return false; // throw
	_port = std::strtol(contents.begin()->c_str(), NULL, 10);
	return true;
}

bool	ServerParser::parseAddr(std::vector<std::string> contents)
{
	if (contents.size() != 1)
		return false; // throw
	_addr = *contents.begin();
	return true;
}

bool	ServerParser::parseServerName(std::vector<std::string> contents)
{
	if (contents.size() != 1)
		return false; // throw
	_server_name = *contents.begin();
	return true;
}

bool	ServerParser::parseIndex(std::vector<std::string> contents)
{
	if (contents.size() != 1)
		return false; // throw
	_index = *contents.begin();
	return true;
}

bool	ServerParser::parseDefaultErrorPage(std::vector<std::string> contents)
{
	if (contents.empty() == true)
		return false; // throw
	std::vector<std::string>::iterator	ite = contents.end();
	for (std::vector<std::string>::iterator it = contents.begin(); it != ite; it++)
	{
		_default_error_page += *it;
		_default_error_page += " ";
	}
	_default_error_page.erase(_default_error_page.length() - 1, 1);
	return true;
}

bool	ServerParser::parseClientBodySize(std::vector<std::string> contents)
{
	if (contents.size() != 1)
		return false; // throw
	_client_body_size = std::strtol(contents.begin()->c_str(), NULL, 10);
	return true;
}
