#ifndef SERVERPARSER_HPP
# define SERVERPARSER_HPP

#include <iostream>
#include <list>
#include <string>
#include "../lib/ft/ft.hpp"
#include <vector>
#include "../Parser/Parser.hpp"

class ServerParser : public Parser
{
protected:

	int			_port;
	std::string	_root;
	std::string	_addr;
	std::string	_server_name;
	std::string	_index;
	std::string	_default_error_page;
	int	_client_body_size;
//	std::list<LocationParser>	_locations;
	std::vector<std::string> _blocks;

	void	(ServerParser::*_parsing_func[7])(const std::string&);
public:
	ServerParser();
	ServerParser(const std::string&);
	ServerParser(const ServerParser&);
	~ServerParser();
	ServerParser& operator=(const ServerParser&);

	size_t	parseElement(const std::string& script);
	size_t	parseBlock(const std::string& script);
	
	void	parsePort(const std::string&);
	void	parseRoot(const std::string&);
	void	parseServerName(const std::string&);
	void	parseIndex(const std::string&);
	void	parseDefaultErrorPage(const std::string&);
	void	parseClientBodySize(const std::string&);
	void	parseNoMatchId(const std::string&);
	
	void	setParsingFunctionArray();

	int	getPort() const;
	std::string	getRoot() const;
	std::string	getAddr() const;
	std::string	getServerName() const;
	std::string	getIndex() const;
	std::string	getDefaultErrorPaget() const;
	int	getClientBodySize() const;
	std::vector<std::string>	getLocations() const;
};

#endif
