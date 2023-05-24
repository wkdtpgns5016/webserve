#include "ft.hpp"

std::string	ft::readFileIntoString(std::string filename)
{
    std::ifstream f(filename);
    std::string str;

    if (!f.good() || !f.is_open())
	{
		return (str);
	}

    if(f)
    {
        std::ostringstream ss;
        ss << f.rdbuf();
        str = ss.str();
    }
    return str;
}
