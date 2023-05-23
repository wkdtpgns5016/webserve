#include "ft.hpp"

size_t ft::stoul(std::string str)
{
    size_t i = 0;
	std::stringstream ss(str);

    ss >> i;
    return (i);
}
