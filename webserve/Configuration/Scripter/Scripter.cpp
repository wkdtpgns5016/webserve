#include "Scripter.hpp"

/**
 * @details 연속정인 개행과 공백들의 끝을 가르킵니다.
 * @param[in] str 문자열
 * @param[in] pos 문자열의 첫번째 인덱스
 * @param[out] pos 마지막 인덱스 + 1
 */
size_t	Scripter::jumpTrash(const std::string& str, size_t pos) const
{
	while (std::isspace(str[pos], std::locale()) == true || str[pos] == '\n')
		pos++;
	return pos;
}

size_t	Scripter::jumpBackTrash(const std::string& str, size_t end) const
{
	size_t	pos = end - 1;
	while (std::isspace(str[pos], std::locale()) == true || str[pos] == '\n')
		pos--;
	return pos + 1;
}

/**
 * @details 한 단어의 끝을 가르킵니다. 한 단어란, trash가 아닌 문자들로 이어진 연속적인 문자열입니다.
 * @param[in] str 문자열
 * @param[in] pos 문자열의 첫번째 인덱스
 * @param[out] pos 마지막 인덱스 + 1
 * @warning 문자열의 시작이 '{'임을 보장해야 합니다. 즉, 이 함수 호출전에 jumpBlockId를 먼저 호출해야 합니다.
 * 
 */

size_t	Scripter::jumpWord(const std::string &str, size_t pos) const
{
	while (std::isspace(str[pos], std::locale()) != true
			&& str[pos] != '\n' && str[pos] != '\0'
			&& str[pos] != '{' && str[pos] != '}' && str[pos] != ';')
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
size_t	Scripter::jumpSimple(const std::string& str, size_t pos) const
{
	pos = str.find(';', pos);
	if (pos == std::string::npos)
		throw unexpectedSimple();
	return pos + 1;
}

/**
 * @details block directives의 identifier의 끝{'{'}을 가르킵니다.
 * @param[in] str 문자열
 * @param[in] pos 문자열의 첫번째 인덱스
 * @param[out] pos 마지막 인덱스 + 1
 * @warning 문자열의 시작이 Trash면 안됩니다. 즉, 이 함수 호출전에 jumpTrash 를 먼저 호출해야 합니다.
 */
size_t	Scripter::jumpBeforeBlock(const std::string& str, size_t pos) const
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
size_t	Scripter::jumpBlock(const std::string& str, size_t pos) const
{
	size_t	end = str.find('}', pos);

	while ((pos = str.find('{', pos + 1)) < end
			&& pos != std::string::npos)
		end = str.find('}', end + 1);
	if (end == std::string::npos)
		throw unexpectedBlock();
	return end + 1;
}

const char* Scripter::unexpectedSimple::what() const throw()
{
	return "unexpected end of file";
}

const char* Scripter::unexpectedBlock::what() const throw()
{
	return "unexpected end of file, expecting \"}\"\n";
}
