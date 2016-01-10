#include "nr3.h"
#include "ran.h"
#include <iostream>
#include <conio.h>
#define R             1
#define Total 100000000

using namespace std;
int main(void)
{
    double x,y;
    int counts;
    Ran a(9);
    for (int i=0;i<Total;i++)
    {
        int temp=0;
        x=(2.0*(a.doub())-1.0)*R;
        y=(2.0*(a.doub())-1.0)*R;
        if ( ((x-R)*(x-R) + (y-R)*(y-R)) > R*R ) temp++;
        if ( ((x-R)*(x-R) + (y+R)*(y+R)) > R*R ) temp++;
        if ( ((x+R)*(x+R) + (y-R)*(y-R)) > R*R ) temp++;
        if ( ((x+R)*(x+R) + (y+R)*(y+R)) > R*R ) temp++;
        if ( temp==4) counts++;
    }
    cout << 4*((double)counts)/Total <<endl;
    while(!kbhit());
    return 0;
}
