#ifndef SIMPLEEXCEPTION_HPP
# define SIMPLEEXCEPTION_HPP

#include <iostream>

class SimpleException: public std::exception
{
protected:
	std::string	_line;
public:
	SimpleException(const std::string& type, const std::string& value, const std::string& id);
	~SimpleException() throw();
	const char* what() const throw();
};


// common Exception
class InvalidNumberOfArguments : public SimpleException
{
public:
	InvalidNumberOfArguments(const std::string& value, const std::string& id);
};

//Each Directive Exception

//ListenException
class ListenException: public SimpleException
{
public:
	ListenException(const std::string& type, const std::string& value);
};

class HostNotFound : public ListenException
{
public:
	HostNotFound(const std::string& value);
};
class InvalidPort : public ListenException
{
public:
	InvalidPort(const std::string& value);
};

class NoHost : public ListenException
{
public:
	NoHost(const std::string& value);
};

// client_max_body_size
class ClientMaxBodySizeException: public SimpleException
{
public:
	ClientMaxBodySizeException(const std::string& type, const std::string& value);
};

class InvalidSize: public ClientMaxBodySizeException
{
public:
	InvalidSize(const std::string& value);
};

// autoindex
class AutoIndexException: public SimpleException
{
public:
	AutoIndexException(const std::string& type, const std::string& value);
};

class InvalidAutoIndex : public AutoIndexException
{
public:
	InvalidAutoIndex(const std::string& value);
};

// allow_method
class AllowMethodException: public SimpleException
{
public:
	AllowMethodException(const std::string& type, const std::string& value);
};

class DuplicateMethod : public AllowMethodException
{
public:
	DuplicateMethod(const std::string& value);
};
class InvalidMethod : public AllowMethodException
{
public:
	InvalidMethod(const std::string& value);
};

// default_error_page
class ErrorPageException: public SimpleException
{
public:
	ErrorPageException(const std::string& type, const std::string& value);
};

class InvalidStatus : public ErrorPageException
{
public:
	InvalidStatus(const std::string& line, const std::string& value);
};
class BetweenStatus : public ErrorPageException
{
public:
	BetweenStatus(const std::string& line, const std::string& value);
};

// try_files
class TryFilesException: public SimpleException
{
public:
	TryFilesException(const std::string& type, const std::string& value);
};

class InvalidValue: public TryFilesException{
public:
	InvalidValue(const std::string& value);
};

//cgi_config
class CgiConfigException : public SimpleException
{
public:
	CgiConfigException(const std::string& type, const std::string& value);
};

class NoValue : public CgiConfigException
{
public:
	NoValue(const std::string& value);
};

class InvalidCgiValue : public CgiConfigException
{
public:
	InvalidCgiValue(const std::string& value);
};

//return_value
class ReturnValueException: public SimpleException
{
public:
	ReturnValueException(const std::string& type, const std::string& value);
};

class InvalidStatusCode : public ReturnValueException
{
public:
	InvalidStatusCode(const std::string& value);
};
//unknown
class UnknownDirective : public std::exception
{
protected:
	std::string	_line;
public:
	UnknownDirective(const std::string& value);
	~UnknownDirective() throw();
	const char* what() const throw();
};

class NotAllowed : public std::exception
{
protected:
	std::string	_line;
public:
	NotAllowed(const std::string &value);
	~NotAllowed() throw();
	const char* what() const throw();
};

#endif
