#ifndef PARSER_HPP
# define PARSER_HPP

#include <iostream>
#include <vector>

class Parser
{
public:
	std::string::iterator	jumpTrash(std::string::iterator pos);
	std::pair<std::string::iterator, std::string::iterator> extractElement(std::string::iterator pos, std::string::iterator end);
	std::pair<std::string::iterator, std::string::iterator> extractBlockID(std::string::iterator pos, std::string::iterator end);
	std::pair<std::string::iterator, std::string::iterator>	extractBraces(std::string::iterator pos, std::string::iterator end);
	bool	isAlpha(const char& c) const;

};

#endif
