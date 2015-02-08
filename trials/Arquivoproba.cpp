#include "nr3.h"
#include "ran.h"
#include <iostream>
#include <fstream>
#include <cmath>
#define TotalCounts 1000000
#define pi 3.14159265358979323846
#include "EXfun.h"
using namespace std;
int main(void)
{
    ofstream f;
    f.open("EX.dat");
    // double efxeo(double SampleR, double DetectorR, double SampleW, double z)
    for (int i=0;i<100;i++)  
    {
        cout << i << endl;
        long double r = efxeo(1.5,25,3.0,2.7*(double)i);
        f.precision(15);
        f << i << " " << r << endl;    
    }
    return 0;
}
