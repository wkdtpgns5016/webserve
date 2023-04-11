#include "ft.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

std::vector<std::string> ft::splitBlockString(std::string str) {
    std::vector<std::string> arr;
    std::string token, s;
    std::istringstream iss(str);
    int count = 0;
    int n1, n2;

    while (std::getline(iss, token, '\n'))
    {
        s = s + token + "\n";
        n1 = std::count(token.begin(), token.end(), '{');
        n2 = std::count(token.begin(), token.end(), '}');
        if (count == 0 && n1 == 0)
        {
            s.clear();
            continue;
        }
        count += n1 - n2;
        if (count == 0)
        {
            arr.push_back(s);
            s.clear();
        }
    }
    return (arr);
}