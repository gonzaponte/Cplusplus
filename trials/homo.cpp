#include "nr3.h"
#include "ran.h"
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
int main(void)
{
    int x[100000];
    double n; 
    Ran aleatorio(7);
    for (int i=0;i<100000;i++) x[i]=0;
    while (!kbhit())
    {
          n=100000*aleatorio.doub();
          x[(int)n]++;
    }
    ofstream f;
    f.open("numeros.dat");
    for (int i=0;i<100000;i++) f << i << " " << x[i] << endl;
    return 0;
}
