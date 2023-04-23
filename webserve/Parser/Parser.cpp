#include "Parser.hpp"


size_t	Parser::jumpTrash(const std::string& str, size_t pos)
{
	while (std::isspace(str[pos], std::locale()) == true || str[pos] == '\n')
		pos++;
	return pos;
}

size_t	Parser::jumpElement(const std::string& str, size_t pos)
{
	pos = str.find(';', pos);
	
	return pos + 1;
}

size_t	Parser::jumpBlockId(const std::string& str, size_t pos)
{
	pos = str.find('{', pos);

	return pos;
}

size_t	Parser::jumpBlock(const std::string& str, size_t pos)
{
	size_t	last = str.find('}', pos);

	while ((pos = str.find('{', pos + 1)) < last
			&& pos != std::string::npos)
		last = str.find('}', last + 1);
	return last + 1;
}

size_t	Parser::jumpElementId(const std::string &str, size_t pos)
{
	while (std::isspace(str[pos], std::locale()) != true
			&& str[pos] != '\n' && str[pos] != '\0')
		pos++;
	return pos;
}

size_t	Parser::jumpElementValue(const std::string& str, size_t pos)
{
	pos = str.find(';', pos);

	return pos;
}

std::pair<std::string, std::string>	Parser::divideElementIdAndValue(const std::string &str, size_t pos)
{
	size_t	last;
	std::string	id;
	std::string	value;

	pos = jumpTrash(str, pos);
	last = jumpElementId(str, pos);
	id = str.substr(pos, last - pos);
	pos = last;

	pos = jumpTrash(str, pos);
	last = jumpElementValue(str, pos);
	value = str.substr(pos, last - pos);

	return std::make_pair(id, value);
}

//bool	Parser::isAlpha(const char& c) const
//{
//	if ('a' <= c && c<= 'z' || 'A' <= c && c <= 'Z')
//		return true;
//	return false;
//}
//
//
// iterator function
//
//std::string::iterator	Parser::jumpTrash(std::string::iterator it)
//{
//	while (std::isspace(*it, std::locale()) == true || *it == '\n') 
//		it++;
//	return it;
//}
//
//std::pair<std::string::iterator, std::string::iterator>	Parser::extractElement(std::string::iterator it, std::string::iterator ite)
//{
//	std::string::iterator	last = std::find(it, ite, ';');
//	if (last == ite)
//		throw std::exception();
//	return std::make_pair(it, last + 1);
//}
//
//std::pair<std::string::iterator, std::string::iterator>	Parser::extractBlockID(std::string::iterator it, std::string::iterator ite)
//{
//	std::string::iterator	last = std::find(it, ite, '{');
//	if (last == ite)
//		throw std::exception();
//	return std::make_pair(it, last);
//
//}
//
//std::pair<std::string::iterator, std::string::iterator>	Parser::extractBraces(std::string::iterator it, std::string::iterator ite)
//{
//	std::string::iterator	start = it;
//	std::string::iterator	last = std::find(it, ite, '}');
//
//	while ((it = std::find(it + 1, ite, '{')) < last
//			&& it != ite)
//		last = std::find(last + 1, ite, '}');
//	if (last == ite)
//		throw std::exception();
//	return std::make_pair(start, last + 1);
//}
//
//std::pair<std::string, std::string>	divideElementIdAndValue(const std::string& element)
//{
//	std::string	id;
//	std::string	value;
//
//	std::pair<size_t, size_t> id_pos = extractWord(jumpTrash(element, 0));
//	id = element.substr(jumpTrash(element, 0), );
//}
