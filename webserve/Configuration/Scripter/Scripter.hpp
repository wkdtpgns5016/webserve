#ifndef SCRIPTER_HPP
# define SCRIPTER_HPP

#include <iostream>

class Scripter
{
public:
	size_t	jumpTrash(const std::string& str, size_t pos) const;
	size_t	jumpWord(const std::string &str, size_t pos) const;
	size_t	jumpSimple(const std::string& str, size_t pos) const;
	size_t	jumpBeforeBlock(const std::string& str, size_t pos) const;
	size_t	jumpBlock(const std::string& str, size_t pos) const;
private:
	class unexpectedSimple : public std::exception
	{
	public:
		const char* what() const throw();
	};

	class unexpectedBlock : public std::exception
	{
	public:
		const char* what() const throw();
	};

};

#endif
