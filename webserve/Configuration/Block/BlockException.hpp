#ifndef BLOCKEXCEPTION_HPP
# define BLOCKEXCEPTION_HPP

#include <iostream>

class BlockException : public std::exception
{
protected:
	std::string	_line;
public:
	BlockException(const std::string& error_type, const std::string& id);
	~BlockException() throw();
	const char* what() const throw();
};

class UnknownOrNotAllowed : public BlockException
{
public:
	UnknownOrNotAllowed(const std::string& block_id);
};

class ConsistOfInvalidNumbersOfArguments : public BlockException
{
public:
	ConsistOfInvalidNumbersOfArguments(const std::string& id);
};
#endif
