#include "Parser.hpp"

/** @details 에러페이지 경로 파싱함수
 */
void 	Parser::checkInvalidStatus(const std::string& error_page)
{
	std::vector<std::string> arr = ft::splitString(error_page, " ");
	std::vector<std::string>::iterator it = arr.begin();
	for (; it != arr.end() - 1; it++)
	{
		if (!isNumbers(*it))
			throw InvalidStatus(*it);
		else
		{
			int number = ft::stoi(*it);
			if (number < 300 || number > 599)
			throw InvalidStatus(*it);
		}
	}
}

void	Parser::parseDefaultErrorPage(const std::string& value, Block* block)
{
	if (isInvalidNumberOfArguments(value, 2, false))
		throw InvalidNumberOfArguments(value, "error_page");
	checkInvalidStatus(value);
	block->setDefaultErrorPage(value);
}
