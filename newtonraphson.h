#include <math.h>
#include "funcion.h"
#include "dfuncion.h"
#include "signo.h"
#define precision 1e-8
/*

###################################################################################################
##                                                                                               ##
##                                      Funci�n creada por:                                      ##
##                                     Gonzalo Mart�nez Lema                                     ##
##                                                                                               ##
###################################################################################################

Este programa parte dunha aproximaci�n a unha ra�z e calcula unha aproximaci�n mellor polo m�todo de 
Newton - Raphson. Se hai m�is dunha raiz no intervalo o programa non funcionar� ben.

Argumentos de entrada:
          
- aprox: aproximaci�n "mala" a unha ra�z

Par�metro por defecto:

- precision: diferenza m�xima entre a ra�z e o 0                            por defecto: 10^-8
           
*/
double newtonraphson(double aprox)
{
       /*
       
       Declaro 2 variables; o valor inicial da primeira � o argumento de entrada:
       
       - x1: punto 1 de aproximaci�n � ra�z
       - x2: punto 2 de aproximaci�n � ra�z
       
       */
       double x1=aprox,x2;
       /*
       
       Agora declaro o os valores da funci�n e da s�a 1� derivada no punto x1:
             
       - fx:  valor da funci�n en x1
       - dfx: valor da 1� derivada da funci�n en x1
       
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
           
           Calculo o valor da funci�n e da s�a derivada en x1. Con iso calculo a seguinte
           aproximaci�n x2 e o valor da funci�n nese punto (reciclo a variable 'fx').
           
           */
           fx = funcion(x1);
           dfx=dfuncion(x1);
           x2=x1-fx/dfx;
           fx=funcion(x2);
           /*
           
           Cando 'fc' sexa menor que a precisi�n desexada esa � a ra�z.
           
           */
           if (fabs(fx)<=precision)
           {
              solucion=0;
              return x2;
           }  
           /*
           
           A seguinte condici�n � por se non se atopa ra�z no intervalo.
           
           */
           if (fabs(x2-x1)<(precision*precision))
           {
              solucion=0;
              perror("Non se atopou ra�z nese intervalo");
           }
           /*
           
           Reasigno a x1 o valor de x2 para iterar o proceso.
           
           */
           x1=x2;
       }
}
