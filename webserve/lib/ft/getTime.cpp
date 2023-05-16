#include "ft.hpp"

std::vector<std::string> ft::getTime(time_t timer)
{
    std::string t;
    std::vector<std::string> arr;

    t = std::string(std::ctime(&timer));
    arr = ft::splitString(t, " ");
    return (arr);
}