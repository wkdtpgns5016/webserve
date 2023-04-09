#include "ServerParser.hpp"
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <locale>


ServerParser::ServerParser(const std::string& server_block)
{
	parseServerBlock(server_block);
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


void	removeFirstWhiteSpaces(std::vector<std::string> *block_lines)
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

bool	checkIdentifier(const std::string& line, const std::string& identifier)
{
	size_t	id_length = identifier.length();

	if (line.compare(0, id_length, identifier) == 0
			&& line.size() > id_length
			&& std::isspace(line.at(id_length), std::locale()) == true)
		return true;
	return false;
}

void	parseServerBrace(std::string* script)
{
	if (script->compare(0, 10, "server\n{\n") == 0)
		return ; //throw
	script->erase(0, 10);

	size_t	last_brace_pos = script->find_last_of('}');
	if (script->compare(last_brace_pos - 1, 3, "\n}\n") == 0)
		return; //throw
	script->erase(last_brace_pos - 1, 3);
}

void	parseLocationBlock(std::string* script) //location parser에 location블록을 넘겨주고, script에서 삭제
{
	//ft::splitString(*script);
	//deleteLocationBlock();
}

void	ServerParser::parseServerBlock(const std::string& server_block)
{
	std::string	server_block_cpy = server_block;

	parseServerBrace(&server_block_cpy);
	parseLocationBlock(&server_block_cpy);
	std::vector<std::string> block_lines = ft::splitString(server_block_cpy, ";");
	removeFirstWhiteSpaces(&block_lines);
	parsePort(&block_lines);
}


std::vector<std::string>	extractContents(std::string line)
{
	std::vector<std::string> ret = ft::splitString(line, " ");

	ret.erase(ret.begin());
	return ret;
}

void	ServerParser::parsePort(std::vector<std::string> *block_lines)
{
	std::vector<std::string>::iterator ite = block_lines->end();

	for (std::vector<std::string>::iterator it = block_lines->begin(); it != ite; it++)
	{
		if (checkIdentifier(*it, "listen"))
		{
			std::vector<std::string>	contents = extractContents(*it);
			if (contents.size() != 1)
				return;
			_port = std::strtol(contents.begin()->c_str(), NULL, 10);
			block_lines->erase(it);
		}
	}
}
