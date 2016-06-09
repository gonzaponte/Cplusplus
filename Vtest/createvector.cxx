#include "TimeProfile.hh"
#include <vector>
#include <iostream>
#include <string>
#include <numeric>

inline std::vector<int> Create( unsigned int N )
{
  std::vector<int> out = std::vector<int>();
  out.reserve(N);
  for ( int i=0; i< (int) N; ++i )
    out.emplace_back(i);
  return out;
}

inline double ComputeMean( std::vector<double>& v )
{
  return std::accumulate( v.begin(), v.end(), 0 ) * 1.0/ v.size();
}

inline std::vector<double> NotCopying( unsigned int Ntimes, unsigned int Nelements )
{
  std::vector<double> measurements;
  measurements.reserve(Ntimes);
  
  for ( unsigned int i=0; i<Ntimes; ++i )
  {
    util::TimeProfiler->begin("0");
    std::vector<int> v = Create(Nelements);
    measurements.emplace_back( util::TimeProfiler->end("0",false) );
  }
  return measurements;
}

inline std::vector<double>    Copying( unsigned int Ntimes, unsigned int Nelements )
{
  std::vector<double> measurements;
  measurements.reserve(Ntimes);
  
  std::vector<int> v0 = Create(Nelements);
  for ( unsigned int i=0; i<Ntimes; ++i )
  {
    util::TimeProfiler->begin("1");
    std::vector<int> v(v0);
    measurements.emplace_back( util::TimeProfiler->end("1",false) );
  }
  return measurements;
}

inline std::vector<double> MemCopying( unsigned int Ntimes, unsigned int Nelements )
{
  std::vector<double> measurements;
  measurements.reserve(Ntimes);
  
  std::vector<int> v0 = Create(Nelements);  
  for ( unsigned int i=0; i<Ntimes; ++i )
  {
    util::TimeProfiler->begin("2");
    std::vector<int> v; v.reserve(Nelements);
    memcpy(&v,&v0,sizeof(v0));
    measurements.emplace_back( util::TimeProfiler->end("2",false) );
  }
  return measurements;
}


int main()
{
  const unsigned int Ntimes    = 1000;
  const unsigned int Nelements = 1000000;
 
  util::TimeProfiler->begin("overall0");
  std::vector<double> notvalues = NotCopying(Ntimes,Nelements);
  double Tnot = ComputeMean(notvalues);
  std::cout << "Average time in mode 0: " << Tnot << std::endl;
  util::TimeProfiler->end("overall0");

  util::TimeProfiler->begin("overall1");
  std::vector<double> yesvalues =    Copying(Ntimes,Nelements);
  double Tyes = ComputeMean(yesvalues);
  std::cout << "Average time in mode 1: " << Tyes << std::endl;
  util::TimeProfiler->end("overall1");

  util::TimeProfiler->begin("overall2");
  std::vector<double> memvalues = MemCopying(Ntimes,Nelements);
  double Tmem = ComputeMean(memvalues);
  std::cout << "Average time in mode 2: " << Tmem << std::endl;
  util::TimeProfiler->end("overall2");

  return 0;
}
