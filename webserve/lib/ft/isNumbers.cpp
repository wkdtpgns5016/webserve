#include "ft.hpp"

bool ft::isNumbers(const std::string& str, size_t pos, size_t len)
{
	if (len == std::string::npos)
		len = str.length();
	while (len > 0 && str[pos] 
			&& std::isdigit(str[pos], std::locale()))
	{
		pos++;
		len--;
	}
	if (str[pos] == '\0' || len == 0)
		return true;
	return false;
}