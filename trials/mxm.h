#include <stdio.h>
/*

###################################################################################################
##                                                                                               ##
##                                      Función creada por:                                      ##
##                                     Gonzalo Martínez Lema                                     ##
##                                                                                               ##
###################################################################################################

Esta función calcula o producto matricial de dúas matrices M e N de dimensións
filas x columnas e columnas x filas respectivamente. O resultado que dá é unha 
matriz cadrada R de dimensións filas x filas.

***************************************************************************************************
***************************************************************************************************
**                                                                                               **
**                                         IMPORTANTE:                                           **
**   Para chamar a esta función hai que incluir 2 #define antes de incluir a propia función:     **
**   - filas:    define o número de filas da primeira matriz                                     **
**   - columnas: define o número de columnas da primeira matriz                                  **
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
       Defino os 3 índices necesarios para correr os bucles
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
               Anulo o elemento que vou calcular porque servirá de acumulador. Corro o bucle sobre
               tódolos elementos que se suman.
               */
               R[i][j]=0.0;
               for (k=0;k<columnas ;k++)
               {
                   R[i][j] += M[i][k] * N[k][j];
               }
           }
       }
       /*
       Fin da función
       */
       return;
}
