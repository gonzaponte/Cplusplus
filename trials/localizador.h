#include <math.h>
#include "funcion.h"
#include "signo.h"
#define intervalos 1000
/*

###################################################################################################
##                                                                                               ##
##                                      Funci�n creada por:                                      ##
##                                     Gonzalo Mart�nez Lema                                     ##
##                                                                                               ##
###################################################################################################

Este programa localiza � raiz dunha funci�n nun intervalo dado. Unha mellor aproximaci�n obtense 
con outros m�todos m�is eficientes. Se hai m�is dunha raiz o programa s� dar� a primeira.

Argumentos de entrada:
          
- minimo: m�nimo do intervalo onde se busca a ra�z
- maximo: m�ximo do intervalo onde se busca a ra�z
- min:    m�nimo do subintervalo onde se atopa a ra�z
- max:    m�ximo do subintervalo onde se atopa a ra�z

Par�metro por defecto:

- intervalos: n�mero de intervalos nos que se subdivide o intervalo inicial;   por defecto: 1000
           
*/
int localizador(double minimo, double maximo,double *min,double *max)
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
       - raiz:  variable que controla o fluxo do bucle
       - i:     �ndice do bucle
       
       */
       double delta;
       int    solucion=1,i;
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
       /*
       
       Anulo o �ndice que usarei para comprobar onde est� a raiz.
       Comparo o signo da funci�n en dous puntos consecutivos; se este cambia asocio a min e max
       os valores deses dous puntos. Se se atopa raiz dev�lvese 1; se non se atopa, 0.
       
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
