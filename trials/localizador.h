#include <math.h>
#include "funcion.h"
#include "signo.h"
#define intervalos 1000
/*

###################################################################################################
##                                                                                               ##
##                                      Función creada por:                                      ##
##                                     Gonzalo Martínez Lema                                     ##
##                                                                                               ##
###################################################################################################

Este programa localiza á raiz dunha función nun intervalo dado. Unha mellor aproximación obtense 
con outros métodos máis eficientes. Se hai máis dunha raiz o programa só dará a primeira.

Argumentos de entrada:
          
- minimo: mínimo do intervalo onde se busca a raíz
- maximo: máximo do intervalo onde se busca a raíz
- min:    mínimo do subintervalo onde se atopa a raíz
- max:    máximo do subintervalo onde se atopa a raíz

Parámetro por defecto:

- intervalos: número de intervalos nos que se subdivide o intervalo inicial;   por defecto: 1000
           
*/
int localizador(double minimo, double maximo,double *min,double *max)
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
       - raiz:  variable que controla o fluxo do bucle
       - i:     índice do bucle
       
       */
       double delta;
       int    solucion=1,i;
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
       /*
       
       Anulo o índice que usarei para comprobar onde está a raiz.
       Comparo o signo da función en dous puntos consecutivos; se este cambia asocio a min e max
       os valores deses dous puntos. Se se atopa raiz devólvese 1; se non se atopa, 0.
       
       */
       i=0;
       while (solucion)
       {
           if (signo(y[i++])!=signo(y[i]))
           {
              solucion=0;
              *max=x[i--];
              *min=x[i];
              return 1;
           }
           if ((i==(intervalos-1))&&(raiz==1))
           {
              solucion=0;
              return 0;
           }
       }
}
