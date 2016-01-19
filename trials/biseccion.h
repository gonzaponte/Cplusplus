#include <math.h>
#include "funcion.h"
#include "signo.h"
#define precision 0.000001
/*

###################################################################################################
##                                                                                               ##
##                                      Función creada por:                                      ##
##                                     Gonzalo Martínez Lema                                     ##
##                                                                                               ##
###################################################################################################

Este programa calcula unha aproximación á raiz dunha función nun intervalo dado polo método da 
bisección. Se hai máis dunha raiz no intervalo o programa non funcionará ben.

Argumentos de entrada:
          
- minimo: mínimo do intervalo onde se busca a raíz
- maximo: máximo do intervalo onde se busca a raíz

Parámetro por defecto:

- precision: diferenza máxima entre a raíz e o 0;                            por defecto: 0.000001
           
*/
double biseccion(double minimo, double maximo)
{
       /*
       
       Declaro 3 variables cuxos valores iniciais veñen dados polos argumentos de entrada:
       
       - a: define o mínimo do intervalo considerado
       - b: define o máximo do itnervalo considerado
       - c: define o punto medio do intervalo considerado
       
       */
       double a=minimo,b=maximo,c=0.5*(a+b);       
       /*
       
       Agora declaro o que serán os valores da función en cada punto:
       
       - fa: valor da función en a
       - fb: valor da función en b
       - fc: valor da función en c
       
       */
       double fa,fb,fc;
       /*
       
       Por outro lado defino outra variable:
           
       - solucion:  variable que controla o fluxo do bucle
       
       Mentres o controlador de fluxo estea en 1 correrase o bucle
       
       */
       int  solucion=1;
       while (solucion)
       {
           /*
           
           Calculo o valor da función nos 3 puntos e compároos.
           
           */
           fa=funcion(a);
           fb=funcion(b);
           fc=funcion(c);
           /*
           
           Se o valor no punto medio é menor que a precisión devolve ese valor; se non, compáranse
           os signos da función entre 'a' e 'c'.
           
           */
           if (fabs(fc)<=precision)
           {
              solucion=0;
              return c;
           }
           else
           {
               /*
               
               Se o signo é distinto entre 'a' e 'c', 'b' toma o valor de 'c' porque a raíz estará
               nese subintervalo; se non é 'a' quen toma o valor de 'c' porque debe estar no outro.
               Ao final recalcúlase o punto medio 'c' de novo.
               
               */
               if (signo(fa)!=signo(fc))   b=c;
               else                        a=c;
               c=0.5*(a+b);
           }
           /*
           
           A seguinte condición é por se non se atopa raíz no intervalo.
           
           */
           if (fabs(c-a)<(precision*precision))
           {
              solucion=0;
              perror("Non se atopou raíz nese intervalo");
           }
       }
}
