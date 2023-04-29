#include "Block.hpp"

/**
 * @details config파일을 문자열 형태의 스크립트로 받아 서버 속성들로 바꿉니다.
 */
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

/**
 * @details 연속정인 개행과 공백들의 끝을 가르킵니다.
 * @param[in] str 문자열
 * @param[in] pos 문자열의 첫번째 인덱스
 * @param[out] pos 마지막 인덱스 + 1
 */
size_t	Block::jumpTrash(const std::string& str, size_t pos) const
{
	while (std::isspace(str[pos], std::locale()) == true || str[pos] == '\n')
		pos++;
	return pos;
}

/**
 * @details simple directives의 끝(';')을 가르킵니다.
 * @param[in] str 문자열
 * @param[in] pos 문자열의 첫번째 인덱스
 * @param[out] pos 마지막 인덱스 + 1
 * @exception 다음 simple directives를 찾지 못할 경우 std::exception을 던집니다.
 * @warning 문자열의 시작이 Trash면 안됩니다. 즉, 이 함수 호출전에 jumpTrash 를 먼저 호출해야 합니다.
 */
size_t	Block::jumpSimple(const std::string& str, size_t pos) const
{
	pos = str.find(';', pos);
	if (pos == std::string::npos)
		throw std::exception();
	return pos + 1;
}

/**
 * @details block directives의 identifier의 끝{'{'}을 가르킵니다.
 * @param[in] str 문자열
 * @param[in] pos 문자열의 첫번째 인덱스
 * @param[out] pos 마지막 인덱스 + 1
 * @warning 문자열의 시작이 Trash면 안됩니다. 즉, 이 함수 호출전에 jumpTrash 를 먼저 호출해야 합니다.
 */
size_t	Block::jumpBlockId(const std::string& str, size_t pos) const
{
	pos = str.find('{', pos);

	return pos;
}


/**
 * @details block directives의 identifier의 끝{'}'}을 가르킵니다.
 * @param[in] str 문자열
 * @param[in] pos 문자열의 첫번째 인덱스
 * @param[out] pos 마지막 인덱스 + 1
 * @warning 문자열의 시작이 '{'임을 보장해야 합니다. 즉, 이 함수 호출전에 jumpBlockId를 먼저 호출해야 합니다.
 * 
 */
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

/**
 * @details 한 단어의 끝을 가르킵니다. 한 단어란, trash가 아닌 문자들로 이어진 연속적인 문자열입니다.
 * @param[in] str 문자열
 * @param[in] pos 문자열의 첫번째 인덱스
 * @param[out] pos 마지막 인덱스 + 1
 * @warning 문자열의 시작이 '{'임을 보장해야 합니다. 즉, 이 함수 호출전에 jumpBlockId를 먼저 호출해야 합니다.
 * 
 */
size_t	Block::jumpWord(const std::string &str, size_t pos) const
{
	while (std::isspace(str[pos], std::locale()) != true
			&& str[pos] != '\n' && str[pos] != '\0')
		pos++;
	return pos;
}

/**
 * @details simple_directives 하나를 id와 value로 나눕니다.
 */
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

/**
 * @details block_directives 하나를 id와 value로 나눕니다.
 */
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

/**
 * @details simple_directives 하나를 파싱합니다.
 */
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

/**
 * @details block_directives 하나를 파싱합니다.
 */
size_t	Block::parseInnerBlock(const std::string& script)
{
	_inner_blocks.push_back(generateInnerBlock(script));
	return script.length();
}


/** @details 포트번호 파싱함수
 */
void	Block::parsePort(const std::string& value)
{
	_port = std::strtol(value.c_str(), NULL, 10);
}

/** @details 루트경로 파싱함수
 */
void	Block::parseRoot(const std::string& value)
{
	_root = value;
}

/** @details 서버이름 파싱함수
 */
void	Block::parseServerName(const std::string& value)
{
	_server_name = value;
}

/** @details 인덱스파일이름 파싱함수
 */
void	Block::parseIndex(const std::string& value)
{
	_index = value;
}

/** @details 에러페이지 경로 파싱함수
 */
void	Block::parseDefaultErrorPage(const std::string& value)
{
	_default_error_page = value;
}

/** @details 클라이언트 바디의 최대바이트수 파싱함수
 */
void	Block::parseClientBodySize(const std::string& value)
{
	_client_body_size = std::strtol(value.c_str(), NULL, 10);
}

/** @details 업로드 경로 파싱함수
 */
void	Block::parseUploadPath(const std::string& value)
{
	_upload_path = value;
}

/** @details 허용메소드 파싱함수
 */
void	Block::parseAllowMethod(const std::string& value)
{
	_allow_method.push_back(value);
}

/** @details 특정 파일형식을 찾을 경로 파싱함수
 */
void	Block::parseTryFiles(const std::string& value)
{
	_try_files.push_back(value);
}

/** @details autoindex여부  파싱함수
 */
void	Block::parseAutoindex(const std::string& value)
{
	if (value == "on")
		_autoindex = true;
	else if (value == "off")
		_autoindex = false;
	else
		throw std::exception();
}

/** @details simple_directives의 id가 이상할 경우의 예외처리를 던지는 파싱함수
 */
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

//private function
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
