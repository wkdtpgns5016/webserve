#ifndef PARSER_HPP
# define PARSER_HPP

#include <exception>
#include <iostream>
#include "../Scripter/Scripter.hpp"
class	Block;

class	Parser
{
private:
	Scripter	_scripter;
	void	(Parser::*_parsing_func[11])(const std::string&, Block*);

	void	parseListen(const std::string&, Block* block);
	void	parseAddr(const std::string& value, Block* block);
	void	parsePort(const std::string&, Block* block);
	void	parseRoot(const std::string&, Block* block);
	void	parseServerName(const std::string&, Block* block);
	void	parseIndex(const std::string&, Block* block);
	void	parseDefaultErrorPage(const std::string&, Block* block);
	void	parseClientBodySize(const std::string&, Block* block);
	void	parseUploadPath(const std::string&, Block* block);
	void	parseAllowMethod(const std::string&, Block* block);
	void	parseTryFiles(const std::string&, Block* block);
	void	parseAutoindex(const std::string&, Block* block);
	void	parseNoMatchId(const std::string&, Block* block);
	std::pair<std::string, std::string>	divideSimpleIdAndValue(const std::string &str, size_t pos) const;
	void	setParsingFunctionArray();
public:
	Parser();
	~Parser();
	Parser(const Parser& other);
	Parser& operator= (const Parser& other);
	size_t	parseSimple(const std::string& script, Block* block);
private:
	
	//listen
	class HostNotFound : public std::exception
	{
	public:
		const char* what() const throw();
	};
	class InvalidPort : public std::exception
	{
	public:
		const char* what() const throw();
	};
	class InvalidNumberOfArguments : public std::exception
	{
	public:
		const char* what() const throw();
	};
	class NoHost : public std::exception
	{
	public:
		const char* what() const throw();
	};
};
#include "../Block/Block.hpp"

#endif
