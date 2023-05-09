#include "Block.hpp"

//compiler
void	Block::compile(const std::string& script)
{
	if (script.length() == std::string::npos)
		throw std::exception();

	size_t	pos = jumpTrash(script, 0);
	size_t	simple_end = pos;
	size_t	block_id_end = pos;
	while (pos + 1 < script.length())
	{
		simple_end = jumpSimple(script, pos);
		block_id_end = jumpBlockId(script, pos);
		if (simple_end < block_id_end)
			pos += parseSimple(script.substr(pos, simple_end - pos));
		else
			pos += parseInnerBlock(script.substr(pos, jumpBlock(script, block_id_end) - pos));
		pos = jumpTrash(script, pos);
	}
}

//jumper
size_t	Block::jumpTrash(const std::string& str, size_t pos) const
{
	while (std::isspace(str[pos], std::locale()) == true || str[pos] == '\n')
		pos++;
	return pos;
}

size_t	Block::jumpSimple(const std::string& str, size_t pos) const
{
	pos = str.find(';', pos);
	if (pos == std::string::npos)
		throw std::exception();
	return pos + 1;
}

size_t	Block::jumpBlockId(const std::string& str, size_t pos) const
{
	pos = str.find('{', pos);

	return pos;
}

size_t	Block::jumpBlock(const std::string& str, size_t pos) const
{
	size_t	end = str.find('}', pos);

	while ((pos = str.find('{', pos + 1)) < end
			&& pos != std::string::npos)
		end = str.find('}', end + 1);
	if (end == std::string::npos)
		throw std::exception();
	return end + 1;
}

size_t	Block::jumpWord(const std::string &str, size_t pos) const
{
	while (std::isspace(str[pos], std::locale()) != true
			&& str[pos] != '\n' && str[pos] != '\0')
		pos++;
	return pos;
}

std::pair<std::string, std::string>	Block::divideSimpleIdAndValue(const std::string &str, size_t pos) const
{
	size_t	end;
	std::string	id;
	std::string	value;

	end = jumpWord(str, pos);
	id = str.substr(pos, end - pos);

	pos = jumpTrash(str, end);
	end = str.length() - 1;
	if (pos < end)
		value = str.substr(pos, end - pos);
	else
		throw std::exception();
	return std::make_pair(id, value);
}

std::pair<std::string, std::string>	Block::divideBlockIdAndValue(const std::string& str, size_t pos) const
{
	size_t	end;
	std::string	id;
	std::string	value;

	end = jumpWord(str, pos);
	id = str.substr(pos, end - pos);

	pos = jumpTrash(str, end) + 1;
	end = str.length() - 1;
	if (pos < end)
		value = str.substr(pos, end - pos);

	return std::make_pair(id, value);
}

//parser
size_t	Block::parseSimple(const std::string& script)
{
	const std::string	simple_id[11] = {"listen", "root", "server_name", "index", "error_page", "client_max_body_size", "upload_path", "allow_method", "try_files", "autoindex", ""};

	std::pair<std::string, std::string>	id_value_pair = divideSimpleIdAndValue(script, 0);
	int i = 0;
	for (; i < 10; i++)
		if (id_value_pair.first == simple_id[i])
			break;
	(this->*_parsing_func[i])(id_value_pair.second);
	return script.length();
}

size_t	Block::parseInnerBlock(const std::string& script)
{
	_inner_blocks.push_back(generateInnerBlock(script));
	return script.length();
}

void	Block::setParsingFunctionArray()
{
	_parsing_func[0] = &Block::parsePort;
	_parsing_func[1] = &Block::parseRoot;
	_parsing_func[2] = &Block::parseServerName;
	_parsing_func[3] = &Block::parseIndex;
	_parsing_func[4] = &Block::parseDefaultErrorPage;
	_parsing_func[5] = &Block::parseClientBodySize;
	_parsing_func[6] = &Block::parseUploadPath;
	_parsing_func[7] = &Block::parseAllowMethod;
	_parsing_func[8] = &Block::parseTryFiles;
	_parsing_func[9] = &Block::parseAutoindex;
	_parsing_func[10] = &Block::parseNoMatchId;
}

void	Block::parsePort(const std::string& value)
{
	_port = std::strtol(value.c_str(), NULL, 10);
}

void	Block::parseRoot(const std::string& value)
{
	_root = value;
}

void	Block::parseServerName(const std::string& value)
{
	_server_name = value;
}

void	Block::parseIndex(const std::string& value)
{
	_index = value;
}

void	Block::parseDefaultErrorPage(const std::string& value)
{
	_default_error_page = value;
}

void	Block::parseClientBodySize(const std::string& value)
{
	_client_body_size = std::strtol(value.c_str(), NULL, 10);
}

void	Block::parseUploadPath(const std::string& value)
{
	_upload_path = value;
}

void	Block::parseAllowMethod(const std::string& value)
{
	_allow_method.push_back(value);
}

void	Block::parseTryFiles(const std::string& value)
{
	_try_files.push_back(value);
}

void	Block::parseAutoindex(const std::string& value)
{
	if (value == "on")
		_autoindex = true;
	else if (value == "off")
		_autoindex = false;
	else
		throw std::exception();
}

void	Block::parseNoMatchId(const std::string& value)
{
	if (value.empty() || 1)
		throw std::exception();
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
	_client_body_size = other._client_body_size;
	_upload_path = other._upload_path;
	_allow_method = other._allow_method;
	_try_files = other._try_files;
	_autoindex = other._autoindex;
}

//getter
const int&	Block::getPort() const { return _port; }
const std::string&	Block::getRoot() const { return _root; }
const std::string&	Block::getAddr() const { return _addr; }
const std::string&	Block::getServerName() const { return _server_name; }
const std::string&	Block::getIndex() const { return _index; }
const std::string&	Block::getDefaultErrorPage() const { return _default_error_page; }
const int&	Block::getClientBodySize() const { return _client_body_size; }
const std::string&	Block::getUploadPath() const { return _upload_path; }
const std::vector<std::string>&	Block::getAllowMethod() const { return _allow_method; }
const std::vector<std::string>&	Block::getTryFiles() const { return _try_files; }
const bool&	Block::getAutoindex() const { return _autoindex; }
const std::vector<Block *>&	Block::getInnerBlock() const { return _inner_blocks; }

//occf
Block::Block()
{
	setParsingFunctionArray();
}

Block::~Block()
{
	std::vector<Block *>::iterator ite = _inner_blocks.end();
	for (std::vector<Block *>::iterator it = _inner_blocks.begin(); it != ite; it++)
		delete *it;
}

