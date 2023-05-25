#include "SimpleException.hpp"

// exception
SimpleException::SimpleException(const std::string& error_type, const std::string& value, const std::string& id)
{
	_line += error_type;
	if (value.empty() == false)
		_line += " in \"" + value + "\"";
	if (id.empty() == false)
		_line += " in the \"" + id + "\" directive";
	_line += "\n";
}
SimpleException::~SimpleException() throw() {}
const char* SimpleException::what() const throw()
{
	return _line.c_str();
}

// common exception
InvalidNumberOfArguments::InvalidNumberOfArguments(const std::string& value, const std::string& id) : SimpleException("invalid number of arguments", value, id) {}

//listen
ListenException::ListenException(const std::string& error_type, const std::string& value) :SimpleException(error_type, value, "listen") {}

HostNotFound::HostNotFound(const std::string& value) : ListenException("host not found", value) {}
InvalidPort::InvalidPort(const std::string& value) : ListenException("invalid port", value) {}
NoHost::NoHost(const std::string& value) : ListenException("no host", value) {}

// client_max_body_size
ClientMaxBodySizeException::ClientMaxBodySizeException(const std::string& error_type, const std::string& value) :SimpleException(error_type, value, "client_max_body_size") {}

InvalidValue::InvalidValue(const std::string& value) : ClientMaxBodySizeException("invalid value", value) {}

// autoindex
AutoIndexException::AutoIndexException(const std::string& error_type, const std::string& value) :SimpleException(error_type, value, "autoindex") {}

InvalidAutoIndex::InvalidAutoIndex(const std::string& value) : AutoIndexException("invalid autoindex", value) {}

// allow_method
TryFilesException::TryFilesException(const std::string& error_type, const std::string& value) :SimpleException(error_type, value, "try_files") {}

DuplicateMethod::DuplicateMethod(const std::string& value) : AllowMethodException("Duplicate Method", value) {}
InvalidMethod::InvalidMethod(const std::string& value) : AllowMethodException("Invalid Method", value) {}

// default_error_page
AllowMethodException::AllowMethodException(const std::string& error_type, const std::string& value) :SimpleException(error_type, value, "allow_method") {}

InvalidStatus::InvalidStatus(const std::string& value) : ErrorPageException("invalid status", value) {}

// try_files
ErrorPageException::ErrorPageException(const std::string& error_type, const std::string& value) :SimpleException(error_type, value, "error_page") {}

InvalidUri::InvalidUri(const std::string& value) : TryFilesException("invalid uri", value) {}

//unnkown
UnknownDirective::UnknownDirective(const std::string& value)
{
	_line += "unnkown directive \"" + value + "\"\n";
}
UnknownDirective::~UnknownDirective() throw() {}
const char* UnknownDirective::what() const throw()
{
	return _line.c_str();
}
