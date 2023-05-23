#include "ft.hpp"


std::vector<std::string> ft::splitString(std::string str, std::string split)
{
    std::vector<std::string> arr;
	char *c = strtok((char*)str.c_str(), split.c_str());
    
	while (c) {
		arr.push_back(c);
		c = strtok(NULL, split.c_str());
	}
    return (arr);
}