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

	void	parseServerBlock(const std::string&);
	void	parsePort(std::vector<std::string> *);

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
