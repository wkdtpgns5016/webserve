#include "./Parser.hpp"
#include <cstddef>
#include <iterator>
#include <sys/wait.h>

/**
 * @details simple_directives 하나를 id와 value로 나눕니다.
 */
std::pair<std::string, std::string>	Parser::divideSimpleIdAndValue(const std::string &str, size_t pos) const
{
	size_t	end;
	std::string	id;
	std::string	value;

	end = _scripter.jumpWord(str, pos);
	id = str.substr(pos, end - pos);

	pos = _scripter.jumpTrash(str, end);
	end = str.length() - 1;
	if (pos < end)
		value = str.substr(pos, end - pos);
	else
		throw std::exception();
	return std::make_pair(id, value);
}

//private function
void	Parser::setParsingFunctionArray()
{
	_parsing_func[0] = &Parser::parseListen;
	_parsing_func[1] = &Parser::parseRoot;
	_parsing_func[2] = &Parser::parseServerName;
	_parsing_func[3] = &Parser::parseIndex;
	_parsing_func[4] = &Parser::parseDefaultErrorPage;
	_parsing_func[5] = &Parser::parseClientMaxBodySize;
	_parsing_func[6] = &Parser::parseUploadPath;
	_parsing_func[7] = &Parser::parseAllowMethod;
	_parsing_func[8] = &Parser::parseTryFiles;
	_parsing_func[9] = &Parser::parseAutoindex;
	_parsing_func[10] = &Parser::parseNoMatchId;
}

/**
 * @details simple_directives 하나를 파싱합니다.
 */
size_t	Parser::parseSimple(const std::string& script, Block* block)
{
	const std::string	simple_id[11] = {"listen", "root", "server_name", "index", "error_page", "client_max_body_size", "upload_path", "allow_method", "try_files", "autoindex", ""};

	std::pair<std::string, std::string>	id_value_pair = divideSimpleIdAndValue(script, 0);
	int i = 0;
	for (; i < 10; i++)
		if (id_value_pair.first == simple_id[i])
			break;
	(this->*_parsing_func[i])(id_value_pair.second, block);
	return script.length();
}

bool	Parser::isNumbers(const std::string& str, size_t pos, size_t len)
{
	if (len == std::string::npos)
		len = str.length();
	while (len > 0 && str[pos] 
			&& std::isdigit(str[pos], std::locale()))
		pos++; len--;
	if (str[pos] == '\0' || len == 0)
		return true;
	return false;
}

/** @details 루트경로 파싱함수
 */
void	Parser::parseRoot(const std::string& value, Block* block)
{
	block->setRoot(value);
}

/** @details 서버이름 파싱함수
 */
void	Parser::parseServerName(const std::string& value, Block* block)
{
	block->setServerName(value);
}

/** @details 인덱스파일이름 파싱함수
 */
void	Parser::parseIndex(const std::string& value, Block* block)
{
	block->setIndex(value);
}

/** @details 에러페이지 경로 파싱함수
 */
void	Parser::parseDefaultErrorPage(const std::string& value, Block* block)
{
	block->setDefaultErrorPage(value);
}

/** @details 클라이언트 바디의 최대바이트수 파싱함수
 */
void	Parser::parseClientMaxBodySize(const std::string& value, Block* block)
{
	size_t pos = value.find("client_max_body_size ");
	if (pos == std::string::npos)
		throw ClientMaxBodySizeException();
	if (pos == 0)
		throw ClientMaxBodySizeException();
	std::string str = value.substr(pos);
	if (!isNumbers(str))
		throw ClientMaxBodySizeException();
	block->setClientMaxBodySize(std::strtol(value.c_str(), NULL, 10));
}

/** @details 업로드 경로 파싱함수
 */
void	Parser::parseUploadPath(const std::string& value, Block* block)
{
	block->setUploadPath(value);
}

/** @details 허용메소드 파싱함수
 */
void	Parser::parseAllowMethod(const std::string& value, Block* block)
{
	size_t	pos = 0;
	size_t	end = 0;

	block->clearAllowMethod();
	while (pos + 1 < value.length())
	{
		end = _scripter.jumpWord(value, pos);
		block->setAllowMethod(value.substr(pos, end - pos));
		pos = _scripter.jumpTrash(value, end);
	}
}

/** @details 특정 파일형식을 찾을 경로 파싱함수
 */
void	Parser::parseTryFiles(const std::string& value, Block* block)
{
	size_t	pos = 0;
	size_t	end = 0;

	block->clearTryFiles();
	while (pos + 1 < value.length())
	{
		end = _scripter.jumpWord(value, pos);
		block->setTryFiles(value.substr(pos, end - pos));
		pos = _scripter.jumpTrash(value, end);
	}
}

/** @details autoindex여부  파싱함수
 */
void	Parser::parseAutoindex(const std::string& value, Block* block)
{
	bool	autoindex;

	if (value == "on")
		autoindex = true;
	else if (value == "off")
		autoindex = false;
	else
		throw std::exception();
	block->setAutoIndex(autoindex);
}

/** @details simple_directives의 id가 이상할 경우의 예외처리를 던지는 파싱함수
 */
void	Parser::parseNoMatchId(const std::string& value, Block* block)
{
	(void)block;
	if (value.empty() || 1)
		throw std::exception();
}

//exception
//listen
Parser::ListenException::ListenException(const std::string& type, const std::string& value)
{
	_line += type;
	if (value.empty())
		_line += " in \"listen\" directive\n";
	else
		_line += " in \"" + value + "\" of the \"listen\" directive\n";
}
Parser::ListenException::~ListenException() throw() {}
const char* Parser::ListenException::what() const throw()
{
	return _line.c_str();
}

Parser::HostNotFound::HostNotFound(const std::string& value) : ListenException("host not found", value) {}
Parser::InvalidPort::InvalidPort(const std::string& value) : ListenException("invalid port", value) {}
Parser::InvalidNumberOfArguments::InvalidNumberOfArguments(const std::string& value) : ListenException("invalid number of arguments", value) {}
Parser::NoHost::NoHost(const std::string& value) : ListenException("no host", value) {}

//client_max_body_size
const char*  Parser::ClientMaxBodySizeException::what() const throw()
{
	return ("Invalid number in \"clinet_max_body_size\" directive\n");
}

//occf
Parser::Parser() { setParsingFunctionArray(); }
Parser::~Parser() {}
Parser::Parser(const Parser& other) { (void)other; }
Parser& Parser::operator=(const Parser& other) { (void)other; return *this; }
