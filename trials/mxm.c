#include <stdio.h>
/*
Esta funci�n calcula o producto matricial de d�as matrices M e N de dimensi�ns
fm x cm e fn x cn respectivamente. O resultado que d� � a matriz R de dimensi�ns
fm x cn.
*/
int mxm(const double M[][], int fm, int cm, const double N[][],int fn, int cn,double R[][])
{
       
       int i,j,k,l;
       if ((fm!=cn)||(cm!=fn))
       {
          throw("As dimensi�ns das matrices non son adecuadas");
       }
       for (i=0;fm>i;i++)
       {
           for (j=0;cn>j;j++)
           {
               R[i][j]=0.0;
               for (k=0;cm>k;k++)
               {
                   R[i][j] += M[i][k] * N[k][j];
               }
           }
       }
       return 0;
}
