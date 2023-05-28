#include "./Parser.hpp"
#include <cstddef>
#include <i386/limits.h>
#include <iterator>
#include <sstream>
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
	if (i != 10)
		(this->*_parsing_func[i])(id_value_pair.second, block);
	else
		(this->*_parsing_func[i])(id_value_pair.first, block);
	return script.length();
}

/** @details 루트경로 파싱함수
 */
void	Parser::parseRoot(const std::string& value, Block* block)
{
	if (isInvalidNumberOfArguments(value, 1, true))
		throw InvalidNumberOfArguments(value, "root");
	block->setRoot(value);
}

/** @details 서버이름 파싱함수
 */
void	Parser::parseServerName(const std::string& value, Block* block)
{
	if (isInvalidNumberOfArguments(value, 0, false))
		throw InvalidNumberOfArguments(value, "upload_path");
	block->setServerName(value);
}

/** @details 인덱스파일이름 파싱함수
 */
void	Parser::parseIndex(const std::string& value, Block* block)
{
	if (isInvalidNumberOfArguments(value, 0, false))
		throw InvalidNumberOfArguments(value, "index");
	block->setIndex(value);
}

/** @details 업로드 경로 파싱함수
 */
void	Parser::parseUploadPath(const std::string& value, Block* block)
{
	if (isInvalidNumberOfArguments(value, 1, true))
		throw InvalidNumberOfArguments(value, "upload_path");
	block->setUploadPath(value);
}


/** @details autoindex여부  파싱함수
 */
void	Parser::parseAutoindex(const std::string& value, Block* block)
{
	bool	autoindex;

	if (isInvalidNumberOfArguments(value, 1, true))
		throw InvalidNumberOfArguments(value, "autoindex");
	if (value == "on")
		autoindex = true;
	else if (value == "off")
		autoindex = false;
	else
		throw InvalidAutoIndex(value);
	block->setAutoIndex(autoindex);
}

/** @details simple_directives의 id가 이상할 경우의 예외처리를 던지는 파싱함수
 */
void	Parser::parseNoMatchId(const std::string& id, Block* block)
{
	(void)block;
	throw UnknownDirective(id);
}

bool	Parser::isInvalidNumberOfArguments(const std::string& value, size_t limit, bool only)
{
	std::vector<std::string> arr;
	if (value.empty())
		return (true);
	arr = ft::splitString(value, " ");
	if (limit != 0)
	{
		if (only && arr.size() != limit)
			return (true);
		if (!only && arr.size() < limit)
			return (true);
	}
	return (false);
}

//occf
Parser::Parser() { setParsingFunctionArray(); }
Parser::~Parser() {}
Parser::Parser(const Parser& other) { (void)other; }
Parser& Parser::operator=(const Parser& other) { (void)other; return *this; }
