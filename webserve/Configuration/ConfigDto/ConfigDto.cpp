#include "ConfigDto.hpp"

ConfigDto::ConfigDto()
{

}

ConfigDto::ConfigDto(ServerBlock* server_block, LocationBlock* location_block)
{
    if (location_block == NULL)
        setConfigWithServerBlock(*server_block);
    else
        setConfigWithLocationBlock(*location_block);
}

ConfigDto::ConfigDto(const ConfigDto& config_dto)
{
    if (this == &config_dto)
        return ;
    _port = config_dto.getPort();
    _root = config_dto.getRoot();
    _addr = config_dto.getAddr();
    _server_name = config_dto.getServerName();
    _index = config_dto.getIndex();
    _default_error_page = config_dto.getDefaultErrorPage();
    _client_body_size = config_dto.getClientMaxBodySize();
    _upload_path = config_dto.getUploadPath();
    _allow_method = config_dto.getAllowMethod();
    _try_files = config_dto.getTryFiles();
    _autoindex = config_dto.getAutoindex();
    _url = config_dto.getUrl();
}

ConfigDto::~ConfigDto()
{

}

ConfigDto& ConfigDto::operator=(const ConfigDto& config_dto)
{
    if (this == &config_dto)
        return (*this);
    _port = config_dto.getPort();
    _root = config_dto.getRoot();
    _addr = config_dto.getAddr();
    _server_name = config_dto.getServerName();
    _index = config_dto.getIndex();
    _default_error_page = config_dto.getDefaultErrorPage();
    _client_body_size = config_dto.getClientMaxBodySize();
    _upload_path = config_dto.getUploadPath();
    _allow_method = config_dto.getAllowMethod();
    _try_files = config_dto.getTryFiles();
    _autoindex = config_dto.getAutoindex();
    _url = config_dto.getUrl();
    return (*this);
}

void ConfigDto::setConfigWithLocationBlock(const LocationBlock& location_block)
{
    _port = location_block.getPort();
    _root = location_block.getRoot();
    _addr = location_block.getAddr();
    _server_name = location_block.getServerName();
    _index = location_block.getIndex();
    _default_error_page = location_block.getDefaultErrorPage();
    _client_body_size = location_block.getClientMaxBodySize();
    _upload_path = location_block.getUploadPath();
    _allow_method = location_block.getAllowMethod();
    _try_files = location_block.getTryFiles();
    _autoindex = location_block.getAutoindex();
    _url = location_block.getUrl();
}

void ConfigDto::setConfigWithServerBlock(const ServerBlock& server_block)
{
    _port = server_block.getPort();
    _root = server_block.getRoot();
    _addr = server_block.getAddr();
    _server_name = server_block.getServerName();
    _index = server_block.getIndex();
    _default_error_page = server_block.getDefaultErrorPage();
    _client_body_size = server_block.getClientMaxBodySize();
    _upload_path = server_block.getUploadPath();
    _allow_method = server_block.getAllowMethod();
    _try_files = server_block.getTryFiles();
    _autoindex = server_block.getAutoindex();
    _url = "";
}

int	ConfigDto::getPort() const { return _port; }
std::string	ConfigDto::getRoot() const { return _root; }
std::string	ConfigDto::getAddr() const { return _addr; }
std::string	ConfigDto::getServerName() const { return _server_name; }
std::string	ConfigDto::getIndex() const { return _index; }
std::string	ConfigDto::getDefaultErrorPage() const { return _default_error_page; }
int	ConfigDto::getClientMaxBodySize() const { return _client_body_size; }
std::string	ConfigDto::getUploadPath() const { return _upload_path; }
std::vector<std::string>	ConfigDto::getAllowMethod() const { return _allow_method; }
std::vector<std::string>	ConfigDto::getTryFiles() const { return _try_files; }
bool	ConfigDto::getAutoindex() const { return _autoindex; }
std::string ConfigDto::getUrl() const { return _url; }