#include "../include/test_client.hpp"

int main(int ac, char *av[])
{
  test_client client("10.28.8.3", atoi(av[1]));
  client.run();
  return (0);
}
