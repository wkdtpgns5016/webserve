#include "./Parser.hpp"

/** @details 허용메소드 파싱함수
 */
bool	Parser::isDuplicateMethod(const std::string& value)
{
	std::vector<std::string> arr = ft::splitString(value, " ");
	std::sort(arr.begin(), arr.end());
	std::vector<std::string>::iterator it = std::unique(arr.begin(), arr.end());
	if (it != arr.end())
		return (true);
	return (false);
}

bool	Parser::isInvalidMethod(const std::string& method)
{
	std::vector<std::string> method_arr;
	method_arr.push_back("GET");
	method_arr.push_back("HEAD");
	method_arr.push_back("POST");
	method_arr.push_back("PUT");
	method_arr.push_back("DELETE");
	size_t count = 0;
	std::vector<std::string>::iterator it = method_arr.begin();
	for (; it != method_arr.end() ; it++)
	{
		if (method != *it)
			count++;
	}
	if (count == method_arr.size())
		return (true);
	return (false);
}

void	Parser::parseAllowMethod(const std::string& value, Block* block)
{
	size_t	pos = 0;
	size_t	end = 0;
	std::string method;

	block->clearAllowMethod();
	if (isInvalidNumberOfArguments(value, "allow_method", 0));
		throw InvalidNumberOfArguments(value, "allow_method");
	if (isDuplicateMethod(value))
		throw DuplicateMethod(value);
	while (pos + 1 < value.length())
	{
		end = _scripter.jumpWord(value, pos);
		method = value.substr(pos, end - pos);
		if (isInvalidMethod(method))
			throw InvalidMethod(value);
		block->setAllowMethod(method);
		pos = _scripter.jumpTrash(value, end);
	}
}

