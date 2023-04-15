#ifndef FT_HPP
#define FT_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

namespace ft
{
    std::string	readFileIntoString(std::string filename);
    std::vector<std::string> splitString(std::string str, std::string split);
    std::vector<std::string> splitBlockString(std::string str);
}

#endif