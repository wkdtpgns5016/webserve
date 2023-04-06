#ifndef FT_HPP
#define FT_HPP

#include <vector>
#include <iostream>

namespace ft
{
    std::vector<std::string> splitString(const std::string& str, const std::string& split);
    std::vector<std::string> splitBlockString(std::string str);
}

#endif