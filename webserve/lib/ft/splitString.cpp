#include "ft.hpp"

std::vector<std::string> ft::splitString(std::string str, std::string split)
{
    std::vector<std::string> arr;
	std::string::size_type n;

    while (str.length() > 0)
    {
        n = str.find(split, 0);
        if (n == std::string::npos)
		{
            arr.push_back(str.substr(0));
			break;
		}
        std::string temp = str.substr(0, n);
        if (temp.length() > 0)
            arr.push_back(temp);
        str = str.substr(n + split.length());
    }
    return (arr);
}