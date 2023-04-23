#ifndef PARSER_HPP
# define PARSER_HPP

#include <iostream>

class Parser
{
public:
	size_t	jumpTrash(const std::string& str, size_t pos);
	size_t	jumpElement(const std::string& str, size_t pos);
	size_t	jumpBlock(const std::string& str, size_t pos);
	size_t	jumpBlockId(const std::string& str, size_t pos);
	size_t	jumpElementId(const std::string& str, size_t pos);
	size_t	jumpElementValue(const std::string& str, size_t pos);

	std::pair<std::string, std::string>	divideElementIdAndValue(const std::string& str, size_t pos);
	
//	bool	isAlpha(const char& c) const;
//
//	std::pair<std::string, std::string>	divideElementIdAndValue(const std::string& element);
//	std::string::iterator	jumpTrash(std::string::iterator it);
//	std::pair<std::string::iterator, std::string::iterator> extractElement(std::string::iterator it, std::string::iterator ite);
//	std::pair<std::string::iterator, std::string::iterator> extractBlockID(std::string::iterator it, std::string::iterator ite);
//	std::pair<std::string::iterator, std::string::iterator>	extractBraces(std::string::iterator it, std::string::iterator ite);

};

#endif
