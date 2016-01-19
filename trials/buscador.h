/*

###################################################################################################
##                                                                                               ##
##                                      Función creada por:                                      ##
##                                     Gonzalo Martínez Lema                                     ##
##                                                                                               ##
###################################################################################################

Esta función busca o elemento de máximo maior absoluto nunha matriz bidimensional e retorna tal
valor e a súa posición.

***************************************************************************************************
***************************************************************************************************
**                                                                                               **
**                                         IMPORTANTE:                                           **
**   Esta función precisa incluir a librería <math.h>                                            **
**                                                                                               **
**   Para chamar a esta función hai que incluir 2 #define antes de incluir a propia función:     **
**        - filas:    número de filas da matriz                                                  **
**        - columnas: número de columnas da matriz                                               **
**                                                                                               **
**   Os argumentos de entrada serán punteiros e veranse modificados ao usar este programa.       **
**                                                                                               **
***************************************************************************************************
***************************************************************************************************

Argumentos de entrada:
          
- m:         matriz en cuestión
- *maximo:   punteiro ao valor do resultado
- *fila:     punteito ao valor da fila do resultado
- *columna:  punteiro ao valor da columna do resultado
           
*/
void buscador(double m[filas][columnas],double *maximo, double *fila, double *columna)
{
     /*
     
     Defino variables de bucles e auxiliares para non andar con punteiros todo o tempo.
     
     */
     double b;
     int i,j,f,c;
     /*
     
     Doulle un valor inicial ao resultado por conveniencia
     
     */
     b=fabs(m[0][0]);
     f=0;
     c=0;
     /*
     
     Recorro tódalas filas e columnas buscando un elemento maior que o que atopei ata entón.
     Se o atopo gardo o valor e sigo buscando ata rematar a matriz.
     
     */
     for (i=0;i<filas;i++)
     {
         for (j=0;j<columnas;j++)
         {
             if (fabs(m[i][j])>b)
             {
                b=fabs(m[i][j]);
                f=i;
                c=j;
             }
         }
     }
     /*
     
     Finalmente asigno os valores aos punteiros de entrada.
     
     */
     *fila=f;
     *columna=c;
     *maximo=b;
     return;
}
