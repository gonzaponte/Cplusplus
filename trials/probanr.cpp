#include "nr3.h"
#include "ran.h"
#include <iostream>
using namespace std;
int main(void)
{
    long int contas = 0;
    long int total; 
    double x, y, r;
    cout << "Introduce o número de contas: "<< endl;
    cin >>  total;
    Ran aleatorio(17);
    for (int i=0;i<total;i++)
    {
          x=aleatorio.doub();
          y=aleatorio.doub();
          r=x*x+y*y;
          if (r<=1.0) contas++;
    }
    cout << 4*((double)contas)/((double)total) << endl;
    cin >> x;
    return 0;
}
