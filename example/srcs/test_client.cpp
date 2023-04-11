#include "../include/test_client.hpp"

int main()
{
  test_client client("10.28.8.3", 8080);
  client.run();
  return (0);
}
