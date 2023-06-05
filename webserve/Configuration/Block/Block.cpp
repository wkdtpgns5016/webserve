#include "Block.hpp"

/**
 * @details config파일을 문자열 형태의 스크립트로 받아 서버 속성들로 바꿉니다.
 */
void	Block::compile(const std::string& script)
{
	size_t	pos = _scripter.jumpTrash(script, 0);
	size_t	simple_end = pos;
	size_t	block_start = pos;
	std::vector<std::string>	block_scripts;

	while (pos + 1 < script.length())
	{
		block_start = _scripter.jumpBeforeBlock(script, pos);
		simple_end = _scripter.jumpSimple(script, pos);
		if (simple_end < block_start)
			pos += _parser->parseSimple(script.substr(pos, simple_end - pos), this);
		else
			pos = saveBlockScripts(script, pos, &block_scripts);
		pos = _scripter.jumpTrash(script, pos);
	}
	parseInnerBlock(block_scripts);
}

size_t	Block::saveBlockScripts(const std::string& script, size_t pos, std::vector<std::string>* block_scripts)
{
	size_t	block_start = _scripter.jumpBeforeBlock(script, pos);
	size_t	block_end = _scripter.jumpBlock(script, block_start);

	block_scripts->push_back(script.substr(pos, block_end - pos));
	return pos + block_scripts->rbegin()->length();
}

/**
 * @details block_directives 하나를 id와 value로 나눕니다.
 */
std::pair<std::string, std::string>	Block::divideBlockIdAndValue(const std::string& str, size_t pos) const
{
	size_t	end;
	std::string	id;
	std::string	value;

	end = _scripter.jumpWord(str, pos);
	id = str.substr(pos, end - pos);

	pos = _scripter.jumpTrash(str, end) + 1;
	end = str.length() - 1;
	if (pos < end)
		value = str.substr(pos, end - pos);

	return std::make_pair(id, value);
}

void	Block::setPort(int port) { _port = port; }
void	Block::setRoot(const std::string& root) { _root = root; }
void	Block::setAddr(unsigned addr) { _addr = addr; }
void	Block::setServerName(const std::string& server_name) { _server_name = server_name; }
void	Block::setIndex(const std::string& index) {_index = index; }
void	Block::setDefaultErrorPage(const std::string& default_error_page) { _default_error_page = default_error_page; }
void	Block::setClientMaxBodySize(size_t client_max_body_size) { _client_max_body_size = client_max_body_size; }
void	Block::setUploadPath(const std::string& upload_path) { _upload_path = upload_path; }
void	Block::setAllowMethod(const std::string& allow_method) { _allow_methods.push_back(allow_method); }
void	Block::setTryFiles(const std::string& try_files) { _try_files.push_back(try_files); }
void	Block::setAutoIndex(bool autoindex) { _autoindex = autoindex; }
void	Block::setCgiConfig(const std::string& extension, const std::string& excuter) { _cgi_configs[extension] = excuter; }
void	Block::setReturnValue(int status_code, const std::string &response_data) { _return_value.first = status_code; _return_value.second = response_data; }
void	Block::clearAllowMethod() { _allow_methods.clear(); }
void	Block::clearTryFiles() { _try_files.clear(); }
void	Block::clearCgiConfig() { _cgi_configs.clear(); }

/**
 * @details block_directives 하나를 파싱합니다.
 */
void	Block::parseInnerBlock(const std::vector<std::string>& block_scripts)
{
	Block *temp;
	std::vector<std::string>::const_iterator	ite = block_scripts.end();

	for (std::vector<std::string>::const_iterator it = block_scripts.begin(); it != ite; it++)
	{
		temp = generateInnerBlock(*it);
		_inner_blocks.push_back(temp);
	}
}

//copier
void	Block::copyWithoutInnerBlock(const Block& other)
{
	_port = other._port;
	_root = other._root;
	_addr = other._addr;
	_server_name = other._server_name;
	_index = other._index;
	_default_error_page = other._default_error_page;
	_client_max_body_size = other._client_max_body_size;
	_upload_path = other._upload_path;
	_allow_methods = other._allow_methods;
	_try_files = other._try_files;
	_autoindex = other._autoindex;
	_cgi_configs = other._cgi_configs;
}

//getter
const int&	Block::getPort() const { return _port; }
const std::string&	Block::getRoot() const { return _root; }
const unsigned int& Block::getAddr() const { return _addr; }
const std::string&	Block::getServerName() const { return _server_name; }
const std::string&	Block::getIndex() const { return _index; }
const std::string&	Block::getDefaultErrorPage() const { return _default_error_page; }
const size_t&	Block::getClientMaxBodySize() const { return _client_max_body_size; }
const std::string&	Block::getUploadPath() const { return _upload_path; }
const std::vector<std::string>&	Block::getAllowMethod() const { return _allow_methods; }
const std::vector<std::string>&	Block::getTryFiles() const { return _try_files; }
const bool&	Block::getAutoindex() const { return _autoindex; }
const std::map<std::string, std::string>& Block::getCgiConfigs() const { return _cgi_configs; }
const std::pair<int, std::string>&	Block::getReturnValue() const { return _return_value; }
const std::vector<Block *>&	Block::getInnerBlock() const { return _inner_blocks; }

//occf
Block::Block() : _parser(new Parser()), _port(80), _addr(0), _client_max_body_size(1024)
{
}

Block::~Block()
{
	delete _parser;
	std::vector<Block *>::iterator ite = _inner_blocks.end();
	for (std::vector<Block *>::iterator it = _inner_blocks.begin(); it != ite; it++)
		delete *it;
}


