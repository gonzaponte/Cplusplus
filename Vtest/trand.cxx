#include <iostream>
#include <random>
#include "TimeProfile.hh"
#include "TRandom2.h"

int main()
{
  TRandom2* rand = new TRandom2(0);
  unsigned long int Ncalls = 1000000000;

  double x;
  for ( unsigned long int n = 0; n<Ncalls; ++n )
    x = rand->Uniform();

  util::TimeProfiler->begin("trandom");
  int ns = util::TimeProfiler->end("trandom");
  std::cout << "Ncalls " << Ncalls << std::endl;
  std::cout << "Time per call (ns)" << ns * 1.0 / Ncalls << std::endl;
}
