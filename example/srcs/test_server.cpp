#include "../include/test_server.hpp"

int main()
{
  test_server serve(500);
  serve.run();
  return (0);
}