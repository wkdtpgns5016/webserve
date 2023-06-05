#include "./Parser.hpp"

void	Parser::parseReturnValue(const std::string& value, Block* block)
{
	size_t	pos = 0;
	size_t	next_pos = 0;
	int	status_code;
	std::string	response_data;

	next_pos = _scripter.jumpWord(value, pos);
	status_code = parseStatusCode(value.substr(pos, next_pos - pos));
	pos = _scripter.jumpTrash(value, next_pos);
	response_data = parseResponseData(value.substr(pos, std::string::npos));
	block->setReturnValue(status_code, response_data);
}

int	Parser::parseStatusCode(const std::string& value)
{
	if (isNumbers(value) == false || isSmallerThanMax(value) == false)
		throw InvalidStatusCode(value);

	std::stringstream ss(value);
	size_t	status_code;
	ss >> status_code;
	if (!(200 <= status_code && status_code <= 599))
		throw InvalidStatusCode(value);
	return status_code;
}

std::string	Parser::parseResponseData(const std::string& value)
{
	if (isInvalidNumberOfArguments(value, 1, true))
		throw InvalidNumberOfArguments(value, "return_value");
	return value;
}
