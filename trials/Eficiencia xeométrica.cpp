//#include "nr3.h"
//#include "ran.h"
#include <iostream>
//#include <conio.h>
#include <cmath>
#include <TRandom.h>
#define SampleR   3.0  //mm
#define SampleW   0.0  //mm
#define Dist	  0.000001 //mm
#define DetectorR 15 //mm
#define TotalCounts 1000000
#define pi 3.14159265358979323846
using namespace std;

int main(void)
{
TRandom *a = new TRandom();

	int i=0,counts=0;
	//Ran a(88);
	
	while(i++<TotalCounts)
	{
		double fi,theta,max=atan(DetectorR/Dist);
		//fi=2*pi*a.doub();
		//theta=acos(pi*a.Doub());
		theta=acos(2*(a->Rndm(i))-1);
		if ( (theta<=max)&&( theta>=-max ) ) counts++;
	}
	cout<<endl;
	cout<<((double)counts)/((double)TotalCounts)<<endl;
	//cin>>counts;
	return 1;
}
