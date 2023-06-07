#ifndef CONFIGDTO_HPP
#define CONFIGDTO_HPP

#include <vector>
#include <iostream>
#include "../ServerBlock/ServerBlock.hpp"

class ConfigDto
{
    private:
    int			_port;
	std::string	_root;
	std::string	_addr;
	std::string	_server_name;
	std::string	_index;
	std::string	_default_error_page;
	int			_client_body_size;
	std::string	_upload_path;
	std::vector<std::string>	_allow_method;
	std::map <std::string, std::string> _cgi_config;
	bool	_autoindex;
	std::pair<int, std::string> _return_value;
	std::string	_url;

    void setConfigWithLocationBlock(const LocationBlock& location_block);
    void setConfigWithServerBlock(const ServerBlock& location_block);

    public:
    ConfigDto();
    ConfigDto(ServerBlock* server_block, LocationBlock* location_block);
    ConfigDto(const ConfigDto& config_dto);
    ~ConfigDto();
    ConfigDto& operator=(const ConfigDto& config_dto);

    int			getPort() const;
	std::string	getRoot() const;
	std::string	getAddr() const;
	std::string	getServerName() const;
	std::string	getIndex() const;
	std::string	getDefaultErrorPage() const;
	int			getClientMaxBodySize() const;
	std::string	getUploadPath() const;
	std::vector<std::string>	getAllowMethod() const;
	bool	getAutoindex() const;
    std::string getUrl() const;
	std::map <std::string, std::string> getCgiConfig() const ;
	std::pair<int, std::string>	getReturnValue() const;
};

#endif