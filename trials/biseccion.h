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

Este programa calcula unha aproximaci�n � raiz dunha funci�n nun intervalo dado polo m�todo da 
bisecci�n. Se hai m�is dunha raiz no intervalo o programa non funcionar� ben.

Argumentos de entrada:
          
- minimo: m�nimo do intervalo onde se busca a ra�z
- maximo: m�ximo do intervalo onde se busca a ra�z

Par�metro por defecto:

- precision: diferenza m�xima entre a ra�z e o 0;                            por defecto: 0.000001
           
*/
double biseccion(double minimo, double maximo)
{
       /*
       
       Declaro 3 variables cuxos valores iniciais ve�en dados polos argumentos de entrada:
       
       - a: define o m�nimo do intervalo considerado
       - b: define o m�ximo do itnervalo considerado
       - c: define o punto medio do intervalo considerado
       
       */
       double a=minimo,b=maximo,c=0.5*(a+b);       
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
           
           Calculo o valor da funci�n nos 3 puntos e comp�roos.
           
           */
           fa=funcion(a);
           fb=funcion(b);
           fc=funcion(c);
           /*
           
           Se o valor no punto medio � menor que a precisi�n devolve ese valor; se non, comp�ranse
           os signos da funci�n entre 'a' e 'c'.
           
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
               Ao final recalc�lase o punto medio 'c' de novo.
               
               */
               if (signo(fa)!=signo(fc))   b=c;
               else                        a=c;
               c=0.5*(a+b);
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
