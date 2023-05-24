#ifndef PARSER_HPP
# define PARSER_HPP

#include <exception>
#include <iostream>
#include "../Scripter/Scripter.hpp"
#include "../lib/ft/ft.hpp"
class	Block;

class	Parser
{
private:
	Scripter	_scripter;
	void	(Parser::*_parsing_func[11])(const std::string&, Block*);

	bool	isNumbers(const std::string& str, size_t pos = 0, size_t len = std::string::npos);
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
	class ListenException : public std::exception
	{
	protected:
		std::string	_line;
	public:
		ListenException(const std::string& type, const std::string& value);
		~ListenException() throw() ; 
		const char* what() const throw();
	};
	class HostNotFound : public ListenException
	{
	public:
		HostNotFound(const std::string& value);
	};
	class InvalidPort : public ListenException
	{
	public:
		InvalidPort(const std::string& value);
	};
	class InvalidNumberOfArguments : public ListenException
	{
	public:
		InvalidNumberOfArguments(const std::string& value);
	};
	class NoHost : public ListenException
	{
	public:
		NoHost(const std::string& value);
	};

	//client_max_body_size
	class ClientMaxBodySizeException : public std::exception
	{
		public:
		virtual const char* what() const throw();
	};

	//autoindex
	class AutoIndexException : public std::exception
	{
		public:
		virtual const char* what() const throw();
	};

	//allow_method
	class AllowMethodException : public std::exception
	{
		protected:
		std::string	_line;
		public:
		AllowMethodException(const std::string& type);
		~AllowMethodException() throw() ; 
		virtual const char* what() const throw();
	};
	class DuplicateMethod : public AllowMethodException
	{
		public:
		DuplicateMethod();
	};
	class InvalidMethod : public AllowMethodException
	{
		public:
		InvalidMethod();
	};
};
#include "../Block/Block.hpp"

#endif
