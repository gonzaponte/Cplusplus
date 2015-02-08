/*

Funci�n a analizar para o programa bisecci�n.

***************************************************************************************************
***************************************************************************************************
**                                                                                               **
**                                         IMPORTANTE:                                           **
**             Se se usan funci�ns non aritm�ticas d�bese incluir a cabeceira math.h             **
**                                                                                               **
***************************************************************************************************
***************************************************************************************************

*/
#define np 22.9
#define nb 0.1123
#define na 15.79
#define nR 0.082
#define nT 430
double funcion (double v)
{     
       double y;
       /* 
       Aqu� vai a funci�n, obviamente non pode ser trascendental
       */
       y = np*v*v*v-(nb*np+nR*nT)*v*v+na*v-na*nb;
       /*
       Fin da funci�n
       */
       return y;
}
