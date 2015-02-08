/*

###################################################################################################
##                                                                                               ##
##                                      Funci�n creada por:                                      ##
##                                     Gonzalo Mart�nez Lema                                     ##
##                                                                                               ##
###################################################################################################

Esta funci�n busca o elemento de m�ximo maior absoluto nunha matriz bidimensional e retorna tal
valor e a s�a posici�n.

***************************************************************************************************
***************************************************************************************************
**                                                                                               **
**                                         IMPORTANTE:                                           **
**   Esta funci�n precisa incluir a librer�a <math.h>                                            **
**                                                                                               **
**   Para chamar a esta funci�n hai que incluir 2 #define antes de incluir a propia funci�n:     **
**        - filas:    n�mero de filas da matriz                                                  **
**        - columnas: n�mero de columnas da matriz                                               **
**                                                                                               **
**   Os argumentos de entrada ser�n punteiros e veranse modificados ao usar este programa.       **
**                                                                                               **
***************************************************************************************************
***************************************************************************************************

Argumentos de entrada:
          
- m:         matriz en cuesti�n
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
     
     Recorro t�dalas filas e columnas buscando un elemento maior que o que atopei ata ent�n.
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
