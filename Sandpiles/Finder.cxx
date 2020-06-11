#include "Sandpile.h"
#include <iostream>
#include <string>


int main(void)
{
  for (int i=0; i<3; ++i) {
    Sandpile a = Sandpile::generate_random();
    std::cout << "Random Sandpile a:" << std::endl
              << a << std::endl;
    a.find_zero();
    a.find_opposite();
    if (!a.zero) continue;
    std::cout << "Zero for Sandpile a:" << std::endl
              << *a.zero << std::endl;
    if (!a.opposite) continue;
    std::cout << "Opposite for Sandpile a:" << std::endl
              << *a.opposite << std::endl;
  }
  return 0;
}
