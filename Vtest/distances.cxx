#include "TimeProfile.hh"
#include <random>
#include <vector>
#include <numeric>
#include <cmath>

const double xmin = -1.0;
const double xmax = +1.0;

namespace util {
    std::default_random_engine Generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> Uniform( xmin, xmax );
    inline double GetRandom(){ return Uniform(Generator); }
}

inline std::vector<double> GetRandomVector( unsigned int N )
{
    std::vector<double> out;
    out.reserve(N);
    for (unsigned int i=0; i<N; ++i)
        out.emplace_back( util::GetRandom() );
    return out;
}

inline double ComputeMean( std::vector<double>& v )
{
    return std::accumulate( v.begin(), v.end(), 0. ) / v.size();
}

inline double ComputeDistance( double x0, double y0, double x1, double y1 )
{
    return sqrt( (x1-x0)*(x1-x0) + (y1-y0)*(y1-y0) );
}

int main()
{
    unsigned int Nexperiments = 1000;
    unsigned int Npoints = 20000000;
    
    std::vector<double> x0,y0,x1,y1;
    std::vector<double> Tdistances, Tpoints;
    double distance;
    
    Tdistances.reserve(Nexperiments);
    Tpoints.reserve(Nexperiments);
    for ( unsigned int i=0; i<Nexperiments; ++i )
    {
        util::TimeProfiler->begin("points");
        x0 = GetRandomVector(Npoints);
        x1 = GetRandomVector(Npoints);
        y0 = GetRandomVector(Npoints);
        y1 = GetRandomVector(Npoints);
        Tpoints.emplace_back( 0.25 * util::TimeProfiler->end("points",false) );
        
        util::TimeProfiler->begin("distances");
        for (unsigned int j=0; j<Npoints; ++j )
            distance = ComputeDistance( x0[j], y0[j], x1[j], y1[j] );
        Tdistances.emplace_back( 1.0 * util::TimeProfiler->end("distances",false) );
    }
    
    std::cout << "Average time in computing random points " << ComputeMean(Tpoints)    << " ms" << std::endl;
    std::cout << "Average time in computing distances     " << ComputeMean(Tdistances) << " ms"<< std::endl;
    
    return 0;
}