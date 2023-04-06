#include "../include/test_webserve.hpp"

int main()
{
    test_webserve serve(500);
    serve.run();
    return (0);
}