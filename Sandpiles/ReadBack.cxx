#include "Sandpile.h"
#include <iostream>

int main(void)
{
  Sandpile s("output/10000000.txt");
  std::cout << "Input matrix is size "
            << s.nrows << " " << s.ncols << std::endl;
  s.expand(200, 200);
  std::cout << "Extended matrix is size "
            << s.nrows << " " << s.ncols << std::endl;
  s.dump_to_file("output/10000000_2.txt");
  return 0;
}
