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

		it->substr(0, space_end);
		if (it->empty())
			block_lines->erase(it);
	}
}

bool	checkId(const std::string& line, const std::string& id)
{
	size_t	id_length = id.length();

	if (line.compare(0, id_length, id) == true
			&& line.size() > id_length
			&& std::isspace(line.at(id_length + 1), std::locale()))
		return true;
	return false;
}
void	ServerParser::parseServerBlock(const std::string& server_block)
{
	//server keyword 삭제함수 필요
	//parseLocationBlock(); //호출해서 location블록을 삭제
	std::vector<std::string> block_lines = ft::splitString(server_block. ";\n");
	removeFirstWhiteSpaces(&block_lines);
	parsePort(&block_lines);
}


std::vector<std::string>	extractContents(std::string line)
{
	std::vector<std::string> ret = ft::splitBlockString(line);

	ret.erase(ret.begin());
	return ret;
}

void	ServerParser::parsePort(std::vector<std::string> *block_lines)
{
	std::vector<std::string>::iterator ite = block_lines->end();

	for (std::vector<std::string>::iterator it = block_lines->begin(); it != ite; it++)
	{
		if (checkId(*it, "listen"))
		{
			std::vector<std::string>	contents = extractContents(*it);
			if (contents.size() != 1)
				return;
			_port = std::strtol(contents.begin()->c_str(), NULL, 10);
			block_lines->erase(it);
		}
	}
}
