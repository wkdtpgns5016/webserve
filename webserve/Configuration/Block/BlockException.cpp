#include "BlockException.hpp"

BlockException::BlockException(const std::string& error_type, const std::string& id)
{
	_line += "\"" + id + "\" directive is ";
	_line += error_type;
	_line += "\n";
}

BlockException::~BlockException() throw() {}

const char* BlockException::what() const throw()
{
	return _line.c_str();
}

UnknownOrNotAllowed::UnknownOrNotAllowed(const std::string& id) : BlockException("unknown or not allowed", id) {}
ConsistOfInvalidNumbersOfArguments::ConsistOfInvalidNumbersOfArguments(const std::string& id) : BlockException("consist of invalid numbers of arguments", id) {}
