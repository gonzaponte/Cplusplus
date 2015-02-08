/*

###################################################################################################
##                                                                                               ##
##                                      Función creada por:                                      ##
##                                     Gonzalo Martínez Lema                                     ##
##                                                                                               ##
###################################################################################################

Este programa resolve un sistema de ecuacións polo método de Gauss sen pivoteo. A entrada debe ser
en forma de matriz de coeficientes ampliada (dimensións d x d+1)

***************************************************************************************************
***************************************************************************************************
**                                                                                               **
**                                         IMPORTANTE:                                           **
**   Para chamar a esta función hai que incluir 1 #define antes de incluir a propia función:     **
**        - variables: número de variables do sistema de ecuacións                               **
**                                                                                               **
**   Os argumentos de entrada veranse modificados ao usar este programa.                         **
**                                                                                               **
***************************************************************************************************
***************************************************************************************************

Argumentos de entrada:
          
- M: matriz ampliada a resolver
- x: vector de variables das ecuacións
           
*/
void gauss_sp(double m[variables][variables+1], double x[variables])
{
     /*
     
     Defino unha variable para aforrar tempo de execución e os índices dos bucles.
     
     */
     double a;
     int i,j,k;
     /*
     
     Corro por tódalas filas e as columnas e fago que a matriz sexa triangular superior facendo
     ceros mediante combinacións lineais nas filas.
     
     */
     x[0]=0.0;
     for (i=0;i<variables-1;i++)           /* columnas */
     {
         x[i+1]=0.0;
         for (j=i+1;j<variables;j++)       /* filas */
         {
             a=m[j][i]/m[i][i];            /* factor da combinación lineal */
             for (k=0;k<=variables;k++)
             {
                 m[j][k]-=(a*m[i][k]);
             }
         }
     }
     /*
     
     Por substitución directa calculo as variables.
     
     */
     for (i=variables-1;i+1;i--)
     {
         x[i]=m[i][variables];
         for (j=i+1;j<variables;j++)
         {
             x[i]-= m[i][j]*x[j];
         }
         x[i]/=m[i][i];
     }
     /*
     
     Fin da función.
     
     */
     return;
}
