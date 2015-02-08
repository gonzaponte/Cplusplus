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

Este programa calcula unha aproximación á raiz dunha función nun intervalo dado polo método de 
régula falsi. Se hai máis dunha raiz no intervalo o programa non funcionará ben.

Argumentos de entrada:
          
- minimo: mínimo do intervalo onde se busca a raíz
- maximo: máximo do intervalo onde se busca a raíz

Parámetro por defecto:

- precision: diferenza máxima entre a raíz e o 0                            por defecto: 0.000001
           
*/
double regulafalsi(double minimo, double maximo)
{
       /*
       
       Declaro 3 variables cuxos valores iniciais veñen dados polos argumentos de entrada:
       
       - a: define o mínimo do intervalo considerado
       - b: define o máximo do itnervalo considerado
       - c: define o punto no cal a recta que une (a,fa) e (b,fb) corta o eixo
       
       */
       double a=minimo,b=maximo,c;       
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
           
           Calculo o valor da función nos extremos e con iso calculo o punto 'c' e o valor da 
           función en 'c'.
           
           */
           fa=funcion(a);
           fb=funcion(b);
           c=a-fa*(b-a)/(fb-fa);      
           fc=funcion(c);
           /*
           
           Se 'fc' é menor que a precisión desexada esa é a raíz, se non comparo os signos de
           'fa' e 'fc'.
           
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
               
               */
               if (signo(fa)!=signo(fc))   b=c;
               else                        a=c;
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
