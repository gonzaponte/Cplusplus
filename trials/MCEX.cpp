#include "nr3.h"
#include "ran.h"
#include <iostream>
#include <conio.h>
#include <cmath>
#define TotalCounts 10000000
#define pi 3.14159265358979323846

using namespace std;

int main(void)
{
    // Poño os contadores a cero, defino os xeradores de aleatorios e as variables de entrada
	int i=0,counts=0;
	Ran a(88),b(77);
	double SampleR,SampleW,z,DetectorR;
	
	// Pido os valores destas variables
	
    cout<<"Cal e o raio da mostra?         (mm)  "; cin>>SampleR;   cout<<endl;
    cout<<"Cal e o raio do detector?       (mm)  "; cin>>DetectorR; cout<<endl;
    cout<<"Cal e o espesor da mostra?      (mm)  "; cin>>SampleW;   cout<<endl;
    cout<<"A que distancia esta a mostra?  (mm)  "; cin>>z;         cout<<endl;
    
    // Declaro as variables aleatorias
    double x0,y0,z0;  // Punto aleatorio da mostra que emite a radiación
    double theta,phi; // Dirección aleatoria na que sae a radiación
    double x,y;       // Puntos aos que chega a radiación no plano do detector
    
    // E comezo o bucle
	while(i++<TotalCounts)
	{
        // Tiro dous aleatorios entre -R e R para x0 e y0 e outro entre 0 e o espesor da mostra 
        // para z0
        x0=SampleR*(2*(b.doub())-1);
        y0=SampleR*(2*(b.doub())-1);
        z0=SampleW*(b.doub());
        
        // Descarto os datos que non son do interior da mostra
        if ((x0*x0+y0*y0)>(SampleR*SampleR)) { i--; continue;}
        
        // Tiro dous aleatorios, un para theta (entre 0 e pi) e outro para phi (entre 0 e 2 pi)
        theta=acos(2*(a.doub())-1);          
        phi=2*pi*(a.doub());
        
        // Posto que z = r cos(theta), r = z/cos(theta). Entón as expresións para x e y redúcense a:
        x=(z+z0)*tan(theta)*cos(phi);
        y=x*tan(phi);
        
        // Se non entra dentro do detector paso a seguinte iteración
        if ( ( (x-x0)*(x-x0) + (y-y0)*(y-y0) ) > (SampleR*SampleR) ) continue;
        
        // Se todo foi ben o detector contou a radiación e sumo
        counts++;
	}
	
	// Finalmente amoso en pantalla o resultado.
    // Divido por dous porque estou contando tanto as que van nunha dirección como na oposta
	cout<<endl;
	cout<<"Eficiencia xeometrica : "<<setprecision(8)<<0.5*((double)counts)/((double)TotalCounts)<<endl;
	cout<<endl;
	
	// Fin
	cout<<"Pulsa unha tecla para pechar"<<endl;
	while (!kbhit());
	return 1;
}
