#include "ft.hpp"

unsigned int ft::convertHex(std::string hex)
{
    unsigned int i;
    std::istringstream iss(hex);
    iss >> std::hex >> i;

    return (i);
}