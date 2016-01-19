/*

###################################################################################################
##                                                                                               ##
##                                      Funci�n creada por:                                      ##
##                                     Gonzalo Mart�nez Lema                                     ##
##                                                                                               ##
###################################################################################################

Este programa calcula a eficiencia xeom�trica dun detector cil�ndrico cunha mostra tam�n cil�ndrica.

***************************************************************************************************
***************************************************************************************************
**                                                                                               **
**                                         IMPORTANTE:                                           **
**   Esta funci�n precisa incluir as librer�as <iostream> e <cmath>, as� como as cabeceiras      **
**   "nr3.h" e "ran.h".                                                                          **
**                                                                                               **
**   Para chamar a esta funci�n hai que incluir 2 #define antes de incluir a propia funci�n:     **
**        - TotalCounts: n�mero total de contas                                                  **
**        - pi: n�mero pi = 3.14159265358979323846                                               **
**                                                                                               **
**   Os argumentos ser�n pasados por valor e ser�n:                                              **
**        - SampleR:     raio da mostra                                                          **
**        - DetectorR:   raio do detector                                                        **
**        - SampleW:     espesor da mostra                                                       **
**        - z:           distancia da mostra ao detector                                         **
**                                                                                               **
***************************************************************************************************
***************************************************************************************************
           
*/
double efxeo(double SampleR, double DetectorR, double SampleW, double z)
{
    // Po�o os contadores a cero, defino os xeradores de aleatorios e as variables de entrada
	int i=0,counts=0;
	Ran a(88),b(77); //88 e 77 son as sementes
    
    // Declaro as variables aleatorias
    double x0,y0,z0,x,y,theta,phi;
    
    // E comezo o bucle
	while(i++<TotalCounts)
	{
        // Tiro dous aleatorios entre -R e R para x0 e y0 e outro entre 0 e o espesor da mostra para z0
        x0=SampleR*(2*(b.doub())-1);
        y0=SampleR*(2*(b.doub())-1);
        z0=SampleW*(b.doub());
        
        // Descarto os datos que non son do interior da mostra
        
        if ((x0*x0+y0*y0)>(SampleR*SampleR)) { i--; continue;}
        
        // Tiro dous aleatorios, un para theta (entre 0 e pi) e outro para phi (entre 0 e 2 pi)
        theta=acos(2*(a.doub())-1);          
        phi=2*pi*(a.doub());
        
        // Posto que z = r cos theta, r = z / cos theta. Ent�n as expresi�ns para x e y red�cense a:
        x=(z+z0)*tan(theta)*cos(phi);
        y=x*tan(phi);
        
        // Se non entra dentro do detector paso a seguinte iteraci�n
        if ( ( (x-x0)*(x-x0) + (y-y0)*(y-y0) ) > ( SampleR*SampleR ) ) continue;
        
        // Se todo foi ben o detector contou a radiaci�n e sumo
        counts++;
	}
	
	// Finalmente retorno o resultado
    // Divido por dous porque estou contando tanto as que van nun sentido como no oposto
     
	long double r = 0.5*((double)counts)/((double)TotalCounts);
	return r;
}
