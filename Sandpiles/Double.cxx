#include "Sandpile.h"
#include <iostream>
#include <chrono>
#include <string>

using namespace std::chrono;

double delta(high_resolution_clock::time_point t0,
             high_resolution_clock::time_point t1){
  return duration_cast<duration<double>>(t1-t0).count();
}


int main(void)
{
  int N = 10000000;
  high_resolution_clock::time_point t0, t1, t2, t3;
  t0 = high_resolution_clock::now();
  Sandpile a("output/" + std::to_string(N) + ".txt");
  std::cout << "input a is " << a.nrows << "x" << a.ncols << " s" << std::endl;
  
  t1 = high_resolution_clock::now();
  std::cout << delta(t0, t1) << " s" << std::endl;
  a.expand(3501, 3501, true);
  std::cout << "a is now " << a.nrows << "x" << a.ncols << " s" << std::endl;
  a *= 2;
  t2 = high_resolution_clock::now();
  std::cout << delta(t1, t2) << " s" << std::endl;
  
  a.dump_to_file("output/" + std::to_string(2*N) + ".txt");
  t3 = high_resolution_clock::now();
  std::cout << delta(t2, t3) << " s" << std::endl;
  std::cout << "Final sandpile contains " << a.sum() << " grains of sand"
            << std::endl;
  return 0;
}
