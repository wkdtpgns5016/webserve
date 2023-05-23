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
    std::string itos(int num);
    int stoi(std::string str);
    std::vector<std::string> getTime(time_t timer);
	size_t stoul(std::string str);
}

#endif
