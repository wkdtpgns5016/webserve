#include "Parser.hpp"

void	Parser::parseListen(const std::string& value, Block* block)
{
	size_t	pos;

	if (isInvalidNumberOfArguments(value, 0, false))
		throw InvalidNumberOfArguments(value, "listen");
	pos = value.find(':');
	if (pos == std::string::npos)
	{
		if (isNumbers(value) == true)
		{
			parsePort(value, block);
			block->setAddr(0);
		}
		else
		{
			parseAddr(value, block);
			block->setPort(80);
		}
	}
	else 
	{
		parseAddr(value.substr(0, pos), block);
		parsePort(value.substr(pos + 1), block);
	}
}

/** @details 포트번호 파싱함수
 */
void	Parser::parsePort(const std::string& value, Block* block)
{
	if (isNumbers(value) == false)
		throw InvalidPort(value);

	long port_num = std::strtol(value.c_str(), NULL, 10);
	if (port_num < 0 || 65535 < port_num)
		throw InvalidPort(value); //invalid port
	block->setPort(port_num);
}

void	Parser::parseAddr(const std::string& value, Block* block)
{
	if (value.empty())
		throw NoHost(value);

	int	num;
	int	addr_num =  0;
	size_t	pos = 0;
	size_t	len = 0;

	for (int i = 0; i < 4; i++)
	{
		if (i != 3)
			len = measureOneSectionLength(value, pos);
		else
			len = std::string::npos;
		num = extractOneSectionNumber(value, pos, len);
		addr_num |= num << i * 8;
		pos += len + 1;
	}
	block->setAddr(addr_num);
}

int	Parser::extractOneSectionNumber(const std::string& value, size_t pos, size_t len)
{
	std::string str;
	int		num = 0;

	str = value.substr(pos, len);
	if (isNumbers(str) == false)
		throw HostNotFound(value);
	num = std::strtol(str.c_str(), NULL, 10);
	if ( num < 0 || 255 < num )
		throw HostNotFound(value);
	return num;
}

size_t	Parser::measureOneSectionLength(const std::string& value, size_t pos)
{
	size_t	next_pos = value.find('.', pos);
	if (next_pos == std::string::npos)
		throw HostNotFound(value);
	return next_pos - pos;
}
