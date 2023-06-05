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
InvalidSize::InvalidSize(const std::string& value) : ClientMaxBodySizeException("invalid value", value) {}

// autoindex
AutoIndexException::AutoIndexException(const std::string& error_type, const std::string& value) :SimpleException(error_type, value, "autoindex") {}

InvalidAutoIndex::InvalidAutoIndex(const std::string& value) : AutoIndexException("invalid value", value) {}

// allow_method
AllowMethodException::AllowMethodException(const std::string& error_type, const std::string& value) :SimpleException(error_type, value, "allow_method") {}
DuplicateMethod::DuplicateMethod(const std::string& value) : AllowMethodException("duplicate method", value) {}
InvalidMethod::InvalidMethod(const std::string& value) : AllowMethodException("invalid method", value) {}

// default_error_page
ErrorPageException::ErrorPageException(const std::string& error_type, const std::string& value) :SimpleException(error_type, value, "error_page") {}

InvalidStatus::InvalidStatus(const std::string& line, const std::string& value) : ErrorPageException(line, value) {}
BetweenStatus::BetweenStatus(const std::string& line, const std::string& value) : ErrorPageException(line, value) {}

// try_files
TryFilesException::TryFilesException(const std::string& error_type, const std::string& value) :SimpleException(error_type, value, "try_files") {}
InvalidValue::InvalidValue(const std::string& value) : TryFilesException("invalid value", value) {}

//cgi_config
CgiConfigException::CgiConfigException(const std::string& type, const std::string& value) : SimpleException(type, value, "cgi_config") {}

InvalidCgiValue::InvalidCgiValue(const std::string& value) : CgiConfigException("invalid value", value) {}
NoValue::NoValue(const std::string& value) : CgiConfigException("no value", value) {}

//unnkown
UnknownDirective::UnknownDirective(const std::string& value) { _line += "unnkown directive \"" + value + "\" variable\n"; }
UnknownDirective::~UnknownDirective() throw() {}
const char* UnknownDirective::what() const throw() { return _line.c_str(); }

NotAllowed::NotAllowed(const std::string &value) { _line += "\"" + value + "\" " +  "is not allowed in config file\n"; }
NotAllowed::~NotAllowed() throw() {}
const char* NotAllowed::what() const throw() { return _line.c_str(); }
