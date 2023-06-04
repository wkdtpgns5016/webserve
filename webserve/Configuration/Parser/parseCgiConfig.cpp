#include "Parser.hpp"
#include <cstddef>
#include <iterator>

void	Parser::parseCgiConfigs(const std::string& value, Block* block)
{
	block->clearCgiConfig();
	if (value.empty() == true)
		throw NoValue(value);

	size_t	pos = 0;
	size_t	next_pos = 0;
	while (pos + 1 < value.length())
	{
		next_pos = _scripter.jumpWord(value, pos);
		parseOneCgiConfig(value.substr(pos, next_pos - pos), block);
		pos = _scripter.jumpTrash(value, next_pos);
	}
}

void	Parser::parseOneCgiConfig(const std::string& value, Block* block)
{
	std::string	extension;
	std::string	excuter;
	size_t	pos = value.find(':');
	if (pos == std::string::npos)
		throw InvalidCgiValue(value);

	extension = value.substr(0, pos);
	excuter = value.substr(pos + 1);
	block->setCgiConfig(extension, excuter);
}
