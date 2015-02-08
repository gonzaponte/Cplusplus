#include <math.h>
#include "funcion.h"
#include "signo.h"
#define intervalos 1000
#define precision 0.001
/*

###################################################################################################
##                                                                                               ##
##                                      Función creada por:                                      ##
##                                     Gonzalo Martínez Lema                                     ##
##                                                                                               ##
###################################################################################################

Este programa calcula polo método da bisección unha primeira aproximación á unha raíz nun intervalo
dado. Unha mellor aproximación obtense con outros métodos máis eficientes.

Argumentos de entrada:
          
- minimo: mínimo do intervalo onde se busca a raíz
- maximo: máximo do intervalo onde se busca a raíz

Parámetros por defecto:

- intervalos: número de intervalos nos que se subdivide o intervalo inicial;   por defecto: 1000
- precision:  precisión coa cal se distingue a raíz;                           por defecto  0.001
           
*/
void biseccion(double minimo, double maximo,double *min,double *max)
{
       /*
       
       Declaro vectores:
       
       - x: vector de puntos nos que avalío a función
       - y: vector de resultados
       
       */ 
       double x[intervalos],y[intervalos];
       /*
       
       Por outro lado defino:
       
       - delta: separación entre puntos
       - aprox: aproximación á raíz da ecuación
       - i,j: índices de bucles
       
       */
       double delta;
       int    raiz=1,i,j;
       /*
       
       Asigno valor a delta     
       
       */
       delta=(maximo-minimo)/intervalos;
       /*
       
       Corro un bucle definindo puntos e avaliando a función neles; gardo os valores nos vectores
         
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
