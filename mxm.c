#include <stdio.h>
/*
Esta función calcula o producto matricial de dúas matrices M e N de dimensións
fm x cm e fn x cn respectivamente. O resultado que dá é a matriz R de dimensións
fm x cn.
*/
int mxm(const double M[][], int fm, int cm, const double N[][],int fn, int cn,double R[][])
{
       
       int i,j,k,l;
       if ((fm!=cn)||(cm!=fn))
       {
          throw("As dimensións das matrices non son adecuadas");
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
