#include "nr3.h"
#include "ran.h"
#include <iostream>
#include <cmath>
#include <conio.h>
#define l 500
// Dirección (1,1,1)
#define x0 -250
#define y0 -250
#define z0 500
// Enerxía
#define E 0.511

using namespace std;
int main(void)
{
    double mx[l],my[l],mz[4*l];
    Ran a(9);
    for (int i=0;i<l;i++)
    {
        mx[i] = -0.5*l+(double)i;
        my[i] = mx[i];
        mz[i] = (double) i;
    }
    double x=x0, y=y0, z=z0;
    double dirx[1000], diry[1000],dirz[1000];
    double cte=0.01/sqrt(2);
    for (int i=0;i<1000;i++)
    {
        dirx[i] = x0 + cte*(double)i;
        diry[i] = y0 + cte*(double)i;
        dirz[i] = z0 + cte*(double)i;
    }
    while (!kbhit())
    {
          
    }
}
