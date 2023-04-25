#include "ft.hpp"

std::string ft::itos(int num)
{
	std::stringstream ss;

    ss << num;
    return (ss.str());
}