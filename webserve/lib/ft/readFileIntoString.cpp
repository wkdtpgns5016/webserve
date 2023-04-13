#include "ft.hpp"

std::string	ft::readFileIntoString(std::string filename)
{
    std::ifstream f(filename);
    std::string str;

    if (!f.good() || !f.is_open())
	{
		std::cout << "Error: Do not stream open of file open." << std::endl;
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
