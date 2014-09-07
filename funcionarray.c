#include "constantes.h"
#define filas 3
#define columnas 6
#include "mxm.h"
/*
*/
void main(void)
{
     double M[filas][columnas]={ {6.0 , 2.0 , 3.0 , 7.0 , 8.5 , 86.2} , {61.2 , 12.8 , 0.3 , 0.8 , 0.85 , 0.862} , {6.0 , 2.0 , 3.0 , 7.0 , 8.5 , 86.2} };
     double N[columnas][filas]={ {6.0 , 5.0 , 0.1} , {4.0 , 3.0 , 5.1} , {2.0 , 1.0 , 0.02} , {2.0 , 1.0 , 2.03} , {2.0 , 5.0 , 3.14} , {9.0 , 1.0 , 1.42} };
     double R[filas][filas]={ {0.0 , 0.0 , 0.0} , {0.0 , 0.0 , 0.0} , {0.0 , 0.0 , 0.0} };
     mxm(M,N,R);
     printf("Elemento 1: %f\n\n",R[0][0]);
     printf("Elemento 2: %f\n\n",R[0][1]);
     printf("Elemento 3: %f\n\n",R[0][2]);
     printf("Elemento 4: %f\n\n",R[1][0]);
     printf("Elemento 1: %f\n\n",R[1][1]);
     printf("Elemento 2: %f\n\n",R[1][2]);
     printf("Elemento 3: %f\n\n",R[2][0]);
     printf("Elemento 4: %f\n\n",R[2][1]);
     printf("Elemento 4: %f\n\n",R[2][2]);
     system("pause");
     return;
}
