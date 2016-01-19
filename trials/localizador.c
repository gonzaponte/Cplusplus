#include <math.h>
#include "funcion.h"
#include "signo.h"
#define intervalos 1000
#define precision 0.001
/*

###################################################################################################
##                                                                                               ##
##                                      Funci�n creada por:                                      ##
##                                     Gonzalo Mart�nez Lema                                     ##
##                                                                                               ##
###################################################################################################

Este programa calcula polo m�todo da bisecci�n unha primeira aproximaci�n � unha ra�z nun intervalo
dado. Unha mellor aproximaci�n obtense con outros m�todos m�is eficientes.

Argumentos de entrada:
          
- minimo: m�nimo do intervalo onde se busca a ra�z
- maximo: m�ximo do intervalo onde se busca a ra�z

Par�metros por defecto:

- intervalos: n�mero de intervalos nos que se subdivide o intervalo inicial;   por defecto: 1000
- precision:  precisi�n coa cal se distingue a ra�z;                           por defecto  0.001
           
*/
void biseccion(double minimo, double maximo,double *min,double *max)
{
       /*
       
       Declaro vectores:
       
       - x: vector de puntos nos que aval�o a funci�n
       - y: vector de resultados
       
       */ 
       double x[intervalos],y[intervalos];
       /*
       
       Por outro lado defino:
       
       - delta: separaci�n entre puntos
       - aprox: aproximaci�n � ra�z da ecuaci�n
       - i,j: �ndices de bucles
       
       */
       double delta;
       int    raiz=1,i,j;
       /*
       
       Asigno valor a delta     
       
       */
       delta=(maximo-minimo)/intervalos;
       /*
       
       Corro un bucle definindo puntos e avaliando a funci�n neles; gardo os valores nos vectores
         
       */
       for (i=0;i<intervalos;i++)
       {
           x[i]=minimo + (double)i * delta;
           y[i]=funcion(x[i]);
       }
       i=0;
       do
       {
           if (signo(y[i++])!=signo(y[i]))
           {
              raiz=0;
              *max=y[i--];
              *min=y[i];
           }
           
       }
       while (raiz);
       return;
}
