#include <iostream>
#include <conio.h>
#include <cmath>
using namespace std;
int main(void)
{
    int i=1;
    double inv,suma=0;
    while(!kbhit())
    {
       inv=1.0/((double)i*i++);
       suma+=inv;
       cout<<inv<<"   "<<suma<<endl;
    }
    cout<< sqrt(suma*6)<<endl;
    cin>>i;
}
