#ifndef SERVERPARSER_HPP
# define SERVERPARSER_HPP

#include <iostream>
#include <list>
#include <string>

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
	ServerParser(const ServerParser& other);
	ServerParser& operator=(const ServerParser& other);

public:
	ServerParser(const std::string block_script);
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
