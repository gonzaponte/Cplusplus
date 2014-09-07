#include <math.h>
#include "funcion.h"
#include "signo.h"
#define precision 0.000001
/*

###################################################################################################
##                                                                                               ##
##                                      Funci�n creada por:                                      ##
##                                     Gonzalo Mart�nez Lema                                     ##
##                                                                                               ##
###################################################################################################

Este programa calcula unha aproximaci�n � raiz dunha funci�n nun intervalo dado polo m�todo de 
r�gula falsi. Se hai m�is dunha raiz no intervalo o programa non funcionar� ben.

Argumentos de entrada:
          
- minimo: m�nimo do intervalo onde se busca a ra�z
- maximo: m�ximo do intervalo onde se busca a ra�z

Par�metro por defecto:

- precision: diferenza m�xima entre a ra�z e o 0                            por defecto: 0.000001
           
*/
double regulafalsi(double minimo, double maximo)
{
       /*
       
       Declaro 3 variables cuxos valores iniciais ve�en dados polos argumentos de entrada:
       
       - a: define o m�nimo do intervalo considerado
       - b: define o m�ximo do itnervalo considerado
       - c: define o punto no cal a recta que une (a,fa) e (b,fb) corta o eixo
       
       */
       double a=minimo,b=maximo,c;       
       /*
       
       Agora declaro o que ser�n os valores da funci�n en cada punto:
       
       - fa: valor da funci�n en a
       - fb: valor da funci�n en b
       - fc: valor da funci�n en c
       
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
           
           Calculo o valor da funci�n nos extremos e con iso calculo o punto 'c' e o valor da 
           funci�n en 'c'.
           
           */
           fa=funcion(a);
           fb=funcion(b);
           c=a-fa*(b-a)/(fb-fa);      
           fc=funcion(c);
           /*
           
           Se 'fc' � menor que a precisi�n desexada esa � a ra�z, se non comparo os signos de
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
               
               Se o signo � distinto entre 'a' e 'c', 'b' toma o valor de 'c' porque a ra�z estar�
               nese subintervalo; se non � 'a' quen toma o valor de 'c' porque debe estar no outro.
               
               */
               if (signo(fa)!=signo(fc))   b=c;
               else                        a=c;
           }
           /*
           
           A seguinte condici�n � por se non se atopa ra�z no intervalo.
           
           */
           if (fabs(c-a)<(precision*precision))
           {
              solucion=0;
              perror("Non se atopou ra�z nese intervalo");
           }
       }
}
