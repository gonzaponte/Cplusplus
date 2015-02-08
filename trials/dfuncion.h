/*

Derivada da función a analizar para o programa newtonraphson.

***************************************************************************************************
***************************************************************************************************
**                                                                                               **
**                                         IMPORTANTE:                                           **
**             Se se usan funcións non aritméticas débese incluir a cabeceira math.h             **
**                                                                                               **
***************************************************************************************************
***************************************************************************************************

*/
double dfuncion (double v)
{     
       double y;
       /* 
       Aquí vai a función, obviamente non pode ser trascendental
       */
       y = 3.0*np*v*v-2.0*(nb*np+nR*nT)*v+na;
       /*
       Fin da función
       */
       return y;
}
