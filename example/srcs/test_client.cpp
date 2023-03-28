#include "../../include/test_client.hpp"

int main()
{
  test_client client("127.0.0.1", 500);
  client.run();
  return (0);
}