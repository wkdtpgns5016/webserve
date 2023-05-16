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
	std::vector<std::string>	_try_files;
	bool	_autoindex;
	std::string	_url;

    void setConfigWithLocationBlock(const LocationBlock& location_block);
    void setConfigWithServerBlock(const ServerBlock& location_block);

    public:
    ConfigDto();
    ConfigDto(const ServerBlock& server_block, const LocationBlock& location_block);
    ConfigDto(const ConfigDto& config_dto);
    ~ConfigDto();
    ConfigDto& operator=(const ConfigDto& config_dto);

    int			getPort() const;
	std::string	getRoot() const;
	std::string	getAddr() const;
	std::string	getServerName() const;
	std::string	getIndex() const;
	std::string	getDefaultErrorPage() const;
	int			getClientBodySize() const;
	std::string	getUploadPath() const;
	std::vector<std::string>	getAllowMethod() const;
	std::vector<std::string>	getTryFiles() const;
	bool	getAutoindex() const;
    std::string getUrl() const;
};

#endif