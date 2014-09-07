#include <math.h>
#include "funcion.h"
#include "dfuncion.h"
#include "signo.h"
#define precision 1e-8
/*

###################################################################################################
##                                                                                               ##
##                                      Función creada por:                                      ##
##                                     Gonzalo Martínez Lema                                     ##
##                                                                                               ##
###################################################################################################

Este programa parte dunha aproximación a unha raíz e calcula unha aproximación mellor polo método de 
Newton - Raphson. Se hai máis dunha raiz no intervalo o programa non funcionará ben.

Argumentos de entrada:
          
- aprox: aproximación "mala" a unha raíz

Parámetro por defecto:

- precision: diferenza máxima entre a raíz e o 0                            por defecto: 10^-8
           
*/
double newtonraphson(double aprox)
{
       /*
       
       Declaro 2 variables; o valor inicial da primeira é o argumento de entrada:
       
       - x1: punto 1 de aproximación á raíz
       - x2: punto 2 de aproximación á raíz
       
       */
       double x1=aprox,x2;
       /*
       
       Agora declaro o os valores da función e da súa 1ª derivada no punto x1:
             
       - fx:  valor da función en x1
       - dfx: valor da 1ª derivada da función en x1
       
       */
       double fx,dfx;
       /*
       
       Por outro lado defino outra variable:
           
       - solucion:  variable que controla o fluxo do bucle
             
       Mentres o controlador de fluxo estea en 1 correrase o bucle
       
       */
       int  solucion=1;
       while (solucion)
       {
           /*
           
           Calculo o valor da función e da súa derivada en x1. Con iso calculo a seguinte
           aproximación x2 e o valor da función nese punto (reciclo a variable 'fx').
           
           */
           fx = funcion(x1);
           dfx=dfuncion(x1);
           x2=x1-fx/dfx;
           fx=funcion(x2);
           /*
           
           Cando 'fc' sexa menor que a precisión desexada esa é a raíz.
           
           */
           if (fabs(fx)<=precision)
           {
              solucion=0;
              return x2;
           }  
           /*
           
           A seguinte condición é por se non se atopa raíz no intervalo.
           
           */
           if (fabs(x2-x1)<(precision*precision))
           {
              solucion=0;
              perror("Non se atopou raíz nese intervalo");
           }
           /*
           
           Reasigno a x1 o valor de x2 para iterar o proceso.
           
           */
           x1=x2;
       }
}
