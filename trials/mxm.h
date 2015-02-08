#include <stdio.h>
/*

###################################################################################################
##                                                                                               ##
##                                      Funci�n creada por:                                      ##
##                                     Gonzalo Mart�nez Lema                                     ##
##                                                                                               ##
###################################################################################################

Esta funci�n calcula o producto matricial de d�as matrices M e N de dimensi�ns
filas x columnas e columnas x filas respectivamente. O resultado que d� � unha 
matriz cadrada R de dimensi�ns filas x filas.

***************************************************************************************************
***************************************************************************************************
**                                                                                               **
**                                         IMPORTANTE:                                           **
**   Para chamar a esta funci�n hai que incluir 2 #define antes de incluir a propia funci�n:     **
**   - filas:    define o n�mero de filas da primeira matriz                                     **
**   - columnas: define o n�mero de columnas da primeira matriz                                  **
**                                                                                               **
***************************************************************************************************
***************************************************************************************************

Argumentos de entrada:
           
- Matriz M
- Matriz N
- Matriz R

*/
void mxm (const double M[filas][columnas],const double N[columnas][filas],double R[filas][filas])
{
       /*
       Defino os 3 �ndices necesarios para correr os bucles
       */
       int i,j,k;
       /*
       Corro o bucle en filas e dentro deste o de columnas
       */
       for (i=0;i<filas;i++)
       {
           for (j=0;j<filas;j++)
           {
               /*
               Anulo o elemento que vou calcular porque servir� de acumulador. Corro o bucle sobre
               t�dolos elementos que se suman.
               */
               R[i][j]=0.0;
               for (k=0;k<columnas ;k++)
               {
                   R[i][j] += M[i][k] * N[k][j];
               }
           }
       }
       /*
       Fin da funci�n
       */
       return;
}
