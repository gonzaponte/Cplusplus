#include "nr3.h"
#include "ran.h"
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
int main(void)
{
    int x[1000000];
    double n; 
    Ran aleatorio(7);
    for (int i=0;i<1000000;i++) x[i]=0;
    while (!kbhit())
    {
          n=1000000*aleatorio.doub();
          x[(int)n]++;
    }
    ofstream f;
    f.open("numeros.dat");
    for (int i=0;i<1000000;i++) f << x[i] << endl;
    return 0;
}
