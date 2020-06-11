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
  int N = 20000;
  int n = 3500, m = 3500;
  std::string outputfile = "output/" + std::to_string(N) + ".txt";
  
  high_resolution_clock::time_point t0, t1, t2, t3;
  t0 = high_resolution_clock::now();
  Sandpile a(n+1, m+1);
  a[n/2][m/2] = N;
  t1 = high_resolution_clock::now();
  std::cout << delta(t0, t1) << " s" << std::endl;
  
  a = a + 0;
  t2 = high_resolution_clock::now();
  std::cout << delta(t1, t2) << " s" << std::endl;
  
  a.dump_to_file(outputfile);
  t3 = high_resolution_clock::now();
  std::cout << delta(t2, t3) << " s" << std::endl;
  
  return 0;
}
