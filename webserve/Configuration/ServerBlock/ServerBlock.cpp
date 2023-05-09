#include "ServerBlock.hpp"
#include <exception>

//script constructor
ServerBlock::ServerBlock(const Block& outer_block, const std::string& script)
{
	copyWithoutInnerBlock(outer_block);
	compile(script);
}

std::pair<std::pair<std::string, std::string>, std::string>	ServerBlock::divideLocationBlockIdAndValue(const std::string& str, size_t pos )
{
	size_t	end;
	std::string	id;
	std::string	url;
	std::string	value;

	end = jumpWord(str, pos);
	id = str.substr(pos, end - pos);
	
	pos = jumpTrash(str, end);
	end = jumpWord(str, pos);

	if (str.find('{', end) == std::string::npos)
		throw std::exception();

	pos = jumpTrash(str, end) + 1;
	end = str.length() - 1;
	if (pos < end)
		value = str.substr(pos, end - pos);

	return std::make_pair(std::make_pair(id, url), value);
}

//generateInnerBlock
LocationBlock*	ServerBlock::generateInnerBlock(const std::string& script)
{
	std::pair<std::pair<std::string, std::string>, std::string> id_url_value_pair = divideLocationBlockIdAndValue(script, 0);
	std::pair<std::string, std::string> id_url_pair = id_url_value_pair.first;
	std::string id = id_url_pair.first;
	std::string url = id_url_pair.second;
	std::string	value = id_url_value_pair.second;
	if (id != "location")
		throw std::exception();
	return new LocationBlock(*this, value, url);
}

//OCCF
ServerBlock::ServerBlock() {}
ServerBlock::~ServerBlock() {}