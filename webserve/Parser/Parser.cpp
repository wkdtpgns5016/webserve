#include "Parser.hpp"
#include <cctype>
#include <exception>
#include <locale>
#include <ratio>
#include <sys/_types/_size_t.h>
#include <utility>

std::string::iterator	Parser::jumpTrash(std::string::iterator pos)
{
	while (std::isspace(*pos, std::locale()) == true || *pos == '\n') 
		pos++;
	return pos;
}

bool	Parser::isAlpha(const char& c) const
{
	if ('a' <= c && c<= 'z' || 'A' <= c && c <= 'Z')
		return true;
	return false;
}

std::pair<std::string::iterator, std::string::iterator>	Parser::extractElement(std::string::iterator pos, std::string::iterator end)
{
	std::string::iterator	last = std::find(pos, end, ';');
	if (last == end)
		throw int();
	return std::make_pair(pos, last + 1);
}

std::pair<std::string::iterator, std::string::iterator>	Parser::extractBlockID(std::string::iterator pos, std::string::iterator end)
{
	std::string::iterator	last = std::find(pos, end, '{');
	if (last == end)
		throw std::exception();
	return std::make_pair(pos, last);

}

std::pair<std::string::iterator, std::string::iterator>	Parser::extractBraces(std::string::iterator pos, std::string::iterator end)
{
	std::string::iterator	start = pos;
	std::string::iterator	last = std::find(pos, end, '}');

	while ((pos = std::find(pos + 1, end, '{')) < last
			&& pos != end)
		last = std::find(last + 1, end, '}');
	if (last == end)
		throw std::exception();
	return std::make_pair(start, last + 1);
}
