#include "ft.hpp"

int ft::stoi(std::string str)
{
    int i = 0;
	std::stringstream ss(str);

    ss >> i;
    return (i);
}