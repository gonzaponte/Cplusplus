/*

Función a analizar para o programa bisección.

***************************************************************************************************
***************************************************************************************************
**                                                                                               **
**                                         IMPORTANTE:                                           **
**             Se se usan funcións non aritméticas débese incluir a cabeceira math.h             **
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
       Aquí vai a función, obviamente non pode ser trascendental
       */
       y = np*v*v*v-(nb*np+nR*nT)*v*v+na*v-na*nb;
       /*
       Fin da función
       */
       return y;
}
