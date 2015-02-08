#include <stdio.h>
#define variables 3
#include <math.h>
#include "gauss_cp.h"
void main(void)
{
     double M[variables][variables+1]={{1.0,2.0,-1.0,2.0},{2.0,4.0,5.0,25.0},{3.0,-1.0,-2.0,-5.0}};
     double x[variables]={0.0,0.0,0.0};
     int i;
     gauss_cp(M,x);
     for (i=0;i<variables;i++)
         printf("\n %f \n",x[i]);
     system("pause");
     return;
}
