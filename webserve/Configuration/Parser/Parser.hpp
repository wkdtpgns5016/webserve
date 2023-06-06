#ifndef PARSER_HPP
# define PARSER_HPP

#include <exception>
#include <iostream>
#include "../Scripter/Scripter.hpp"
#include "./SimpleException.hpp"
#include "../../lib/ft/ft.hpp"

class	Block;

class	Parser
{
private:
	Scripter	_scripter;
	void	(Parser::*_parsing_func[13])(const std::string&, Block*);

	bool	isInvalidNumberOfArguments(const std::string& value, size_t limit, bool only);
	bool	isNumbers(const std::string& str, size_t pos = 0, size_t len = std::string::npos);
	bool	isSmallerThanMax(const std::string& num_str);
	bool 	isDuplicateMethod(const std::string& value);
	bool	isInvalidMethod(const std::string& method);
	bool	isServerBlock(Block* block);
	void	checkInvalidStatus(const std::string& error_page);
	int		extractOneSectionNumber(const std::string& value, size_t pos, size_t len);
	size_t	measureOneSectionLength(const std::string& value, size_t pos);

	void	parseListen(const std::string&, Block* block);
	void	parseAddr(const std::string& value, Block* block);
	void	parsePort(const std::string&, Block* block);
	void	parseRoot(const std::string&, Block* block);
	void	parseServerName(const std::string&, Block* block);
	void	parseIndex(const std::string&, Block* block);
	void	parseDefaultErrorPage(const std::string&, Block* block);
	void	parseClientMaxBodySize(const std::string&, Block* block);
	void	parseUploadPath(const std::string&, Block* block);
	void	parseAllowMethod(const std::string&, Block* block);
	void	parseAutoindex(const std::string&, Block* block);
	void	parseNoMatchId(const std::string&, Block* block);
	void	parseCgiConfigs(const std::string&, Block* block);
	void	parseOneCgiConfig(const std::string&, Block* block);

	void	parseReturnValue(const std::string&, Block* block);
	int		parseStatusCode(const std::string&);
	std::string	parseResponseData(const std::string&);

	std::pair<std::string, std::string>	divideSimpleIdAndValue(const std::string &str, size_t pos) const;
	void	setParsingFunctionArray();

public:
	Parser();
	~Parser();
	Parser(const Parser& other);
	Parser& operator= (const Parser& other);
	size_t	parseSimple(const std::string& script, Block* block);

private:
};
#include "../Block/Block.hpp"
#endif
