#include "Parser.hpp"

/** @details 클라이언트 바디의 최대바이트수 파싱함수
 */
bool	Parser::isNumbers(const std::string& str, size_t pos, size_t len)
{
	if (len == std::string::npos)
		len = str.length();
	while (len > 0 && str[pos] 
			&& std::isdigit(str[pos], std::locale()))
	{
		pos++;
		len--;
	}
	if (str[pos] == '\0' || len == 0)
		return true;
	return false;
}

bool	Parser::isSmallerThanMax(const std::string& num_str)
{
	std::stringstream	ss;
	ss << SIZE_T_MAX;
	std::string	str = ss.str();
	if (num_str.length() > str.length())
		return false;
	else if (num_str.length() == str.length())
	{
		if (num_str.compare(str) <= 0)
			return true;
		return false;;
	}
	return true;
}

void	Parser::parseClientMaxBodySize(const std::string& value, Block* block)
{
	if (isInvalidNumberOfArguments(value, 1, true))
		throw InvalidNumberOfArguments(value, "client_max_body_size");
	if (isNumbers(value) == false || isSmallerThanMax(value) == false)
		throw InvalidValue(value);
	
	std::stringstream ss(value);
	size_t	client_max_body_size;
	ss >> client_max_body_size;
	block->setClientMaxBodySize(client_max_body_size);
}
