#include "Parser.hpp"

/** @details 특정 파일형식을 찾을 경로 파싱함수
 */
bool	Parser::isInvalidUri(const std::string& uri)
{
	if (uri.at(0) != '/')
		if (uri.substr(0, 4) != "$uri")
			return (true);
	return (false);
}

void	Parser::parseTryFiles(const std::string& value, Block* block)
{
	size_t	pos = 0;
	size_t	end = 0;
	std::string uri;

	block->clearTryFiles();
	if (isInvalidNumberOfArguments(value, 0, false))
		throw InvalidNumberOfArguments(value, "try_files");
	while (pos + 1 < value.length())
	{
		end = _scripter.jumpWord(value, pos);
		uri = value.substr(pos, end - pos);
		if (isInvalidUri(uri))
			throw InvalidUri(value);
		block->setTryFiles(uri);
		pos = _scripter.jumpTrash(value, end);
	}
}

