#include <iostream>
#include <stdlib.h>

int main(int argc, char **argv) {
  unsigned int dimensions = 0;
  if (argv[1]) {
    dimensions = atoi(argv[1]);
  } else {
    std::cout << "you must provide a number of dimensionssss\n";
    return 0;
  }
  std::cout << "using " << dimensions << " dimensions\n";
  return 0;
}
