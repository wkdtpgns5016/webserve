#ifndef SERVERPARSER_HPP
# define SERVERPARSER_HPP

#include <iostream>
#include <list>
#include <string>
#include "../lib/ft/ft.hpp"
#include <vector>

class ServerParser
{
protected:
	int	_port;
	std::string	_addr;
	std::string	_server_name;
	std::string	_index;
	std::string	_default_error_page;
	int	_client_body_size;
//	std::list<LocationParser>	_locations;

private:
	ServerParser();
	ServerParser(const ServerParser&);
	ServerParser& operator=(const ServerParser&);

	void	parseServerBrace(std::string*);
	void	parseLocationBlock(std::string*);
	void	parseServerBlock(const std::string&);
	
	void	loopForParsing(std::vector<std::string>*, const std::string&, bool (ServerParser::*)(std::vector<std::string>));	bool	parsePort(std::vector<std::string>);

	bool	checkIdentifier(const std::string&, const std::string&);
	void	removeFirstWhiteSpaces(std::vector<std::string> *);
	std::vector<std::string>	extractContents(std::string line);
public:
	ServerParser(const std::string&);
	~ServerParser();

	int	getPort() const;
	std::string	getAddr() const;
	std::string	getServerName() const;
	std::string	getIndex() const;
	std::string	getDefaultErrorPaget() const;
	int	getClientBodySize() const;
	std::string	getLocations() const;
};

#endif
