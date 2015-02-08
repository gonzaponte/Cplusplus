/*

Derivada da funci�n a analizar para o programa newtonraphson.

***************************************************************************************************
***************************************************************************************************
**                                                                                               **
**                                         IMPORTANTE:                                           **
**             Se se usan funci�ns non aritm�ticas d�bese incluir a cabeceira math.h             **
**                                                                                               **
***************************************************************************************************
***************************************************************************************************

*/
double dfuncion (double v)
{     
       double y;
       /* 
       Aqu� vai a funci�n, obviamente non pode ser trascendental
       */
       y = 3.0*np*v*v-2.0*(nb*np+nR*nT)*v+na;
       /*
       Fin da funci�n
       */
       return y;
}
