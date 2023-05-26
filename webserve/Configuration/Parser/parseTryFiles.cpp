#include "Parser.hpp"

/** @details 특정 파일형식을 찾을 경로 파싱함수
 */
void	Parser::checkInvalidUri(const std::string& uri)
{
	std::vector<std::string> arr = ft::splitString(uri, "$");
	std::vector<std::string>::iterator it = arr.begin();
	for (; it != arr.end(); it++)
	{
		size_t pos = (*it).find('/');
		std::string value = (*it).substr(0, pos);
		if (value != "uri")
			throw UnknownDirective(value);
	}
}

void	Parser::parseTryFiles(const std::string& value, Block* block)
{
	size_t	pos = 0;
	size_t	end = 0;
	std::string uri;

	block->clearTryFiles();
	if (isInvalidNumberOfArguments(value, 2, false))
		throw InvalidNumberOfArguments(value, "try_files");
	while (pos + 1 < value.length())
	{
		end = _scripter.jumpWord(value, pos);
		uri = value.substr(pos, end - pos);
		checkInvalidUri(uri);
		block->setTryFiles(uri);
		pos = _scripter.jumpTrash(value, end);
	}
}

