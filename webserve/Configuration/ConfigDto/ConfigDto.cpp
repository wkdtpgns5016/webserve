#include "ConfigDto.hpp"

ConfigDto::ConfigDto()
{

}

ConfigDto::ConfigDto(const ServerBlock& server_block, const LocationBlock& location_block)
{
    setConfigWithLocationBlock(location_block);
    setConfigWithServerBlock(server_block);
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
    _client_body_size = config_dto.getClientBodySize();
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
    _client_body_size = config_dto.getClientBodySize();
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
    _client_body_size = location_block.getClientBodySize();
    _upload_path = location_block.getUploadPath();
    _allow_method = location_block.getAllowMethod();
    _try_files = location_block.getTryFiles();
    _autoindex = location_block.getAutoindex();
    _url = location_block.getUrl();
}

void ConfigDto::setConfigWithServerBlock(const ServerBlock& server_block)
{
    if (_port < 0 || _port > 65535)
        _port = server_block.getPort();
    if (_root.empty())
        _root = server_block.getRoot();
    if (_addr.empty())
        _addr = server_block.getAddr();
    if (_server_name.empty())
        _server_name = server_block.getServerName();
    if (_index.empty())
        _index = server_block.getIndex();
    if (_default_error_page.empty())
        _default_error_page = server_block.getDefaultErrorPage();
    if (_client_body_size <= 0)
        _client_body_size = server_block.getClientBodySize();
    if (_upload_path.empty())
        _upload_path = server_block.getUploadPath();
    if (_allow_method.empty())
        _allow_method = server_block.getAllowMethod();
    if (_try_files.empty())
        _try_files = server_block.getTryFiles();
    if (_autoindex == 0)
        _autoindex = server_block.getAutoindex();
}

int	ConfigDto::getPort() const { return _port; }
std::string	ConfigDto::getRoot() const { return _root; }
std::string	ConfigDto::getAddr() const { return _addr; }
std::string	ConfigDto::getServerName() const { return _server_name; }
std::string	ConfigDto::getIndex() const { return _index; }
std::string	ConfigDto::getDefaultErrorPage() const { return _default_error_page; }
int	ConfigDto::getClientBodySize() const { return _client_body_size; }
std::string	ConfigDto::getUploadPath() const { return _upload_path; }
std::vector<std::string>	ConfigDto::getAllowMethod() const { return _allow_method; }
std::vector<std::string>	ConfigDto::getTryFiles() const { return _try_files; }
bool	ConfigDto::getAutoindex() const { return _autoindex; }
std::string ConfigDto::getUrl() const { return _url; }