#include "nr3.h"
#include "ran.h"
#include <iostream>
#include <conio.h>
#include <cmath>
#define TotalCounts 10000000
#define pi 3.14159265358979323846
using namespace std;

int main(void)
{
	int i=0,counts=0;
	Ran a(88),b(77);
	double SampleR,SampleW,Dist,DetectorR;
    cout<<"Which is the radius of the sample?   (mm)  "; cin>>SampleR;   cout<<endl;
    cout<<"Which is the radius of the detector? (mm)  "; cin>>DetectorR; cout<<endl;
    cout<<"How deep is the sample? (mm)  ";              cin>>SampleW;   cout<<endl;
    cout<<"How far is the sample?  (mm)  ";              cin>>Dist;      cout<<endl;
    double x0,y0,z0,theta,maxup,maxdown,max=atan(DetectorR/Dist);
	while(i++<TotalCounts)
	{
        /*
        x0=SampleR*(b.doub());y0=SampleR*(b.doub());z0=SampleW*(b.doub());
        if ( (x0*x0+y0+y0)>(SampleR*SampleR) )
        {
             i--;
             continue;
        }
        maxup=atan((DetectorR-/)
        */
        fi=2*pi*a.doub();
		theta=acos(2*(a.doub())-1);
		if ( theta<=max ) counts++;
	}
	cout<<endl;
	cout<<"Geometric eficiency: "<<setprecision(8)<<((double)counts)/((double)TotalCounts)<<endl;
	cout<<endl;
	cout<<"Press any key to close"<<endl;
	while (!kbhit());
	return 1;
}
