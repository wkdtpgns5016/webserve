#include "Parser.hpp"

/** @details 에러페이지 경로 파싱함수
 */
bool 	Parser::isInvalidErrorPage(const std::string& error_page)
{
	std::vector<std::string> arr = ft::splitString(error_page, " ");
	if (arr.size() <= 1)
		return (true);
	std::vector<std::string>::iterator it = arr.begin();
	for (; it != arr.end() - 1; it++)
	{
		if (!isNumbers(*it))
			return (true);
	}
	return (false);
}

void	Parser::parseDefaultErrorPage(const std::string& value, Block* block)
{
	if (isInvalidErrorPage(value))
		throw InvalidStatus(value);
	block->setDefaultErrorPage(value);
}
