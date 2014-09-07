#include <stdio.h>
/*
*/
void potencialLJ(double *U,double *phiv,double *phivv,double *fx,double *fy,double *fz)
{
/*
A subrutina potencialLJ calcula a enerx�a potencial dun sistema, a s�a primeira e segunda derivada
e a aceleraci�n resultante a partir do n�mero de part�culas, o lado da caixa o raio de corte e as
posici�ns iniciais.

Declaro variables a usar dentro da subrutina:
-i,j: 		  variables auxiliares para correr nos bucles
-dx,dy,dz:    compo�entes do vector distancia entre d�as part�culas
-D2: 		  m�dulo ao cadrado dese vector
-D2i: 		  inverso do anterior
-D6: 		  inversa da sexta potencia da distancia
-D12:  	      inversa da duod�cima potencia da distancia.
-fmod: 	      parte com�n escalar dos vectores de aceleraci�n.
-DeltaU: 	  correcci�n � enerx�a potencial
-Deltaphiv:   correcci�n � suma da primeira derivada da enerx�a potencial
-Deltaphivv:  correcci�n � suma da segunda derivada da enerx�a potencial
*/
int i,j;
double dx,dy,dz,D2,D2i,D6,D12,fmod,DeltaU,Deltaphiv,Deltaphivv;
/*
Corro o bucle en i dende un ata N-1 e en j de i+1 ata N para non calcular
d�as veces o mesmo.
*/
do i=1,N-1
{
   do j=i+1,N
   {
/*
	Resto os vectores de cada par de part�culas.
*/    
    dx=rx[i]-rx[j];
    dy=ry[i]-ry[j];
    dz=rz[i]-rz[j];
/*
	As seguintes li�as redefinen a distancia cunha part�cula como a da s�a imaxe m�is pr�xima.
*/    
    dx-=ldp*round(dx*ldpi);
	dy-=ldp*round(dy*ldpi);
	dz-=ldp*round(dz*ldpi);
/*
	Calculo o m�dulo ao cadrado e as inversas do m�dulo � sexta e a duod�cima potencia.
*/    
    D2=dx*dx+dy*dy+dz*dz;
/*
	A seguinte condici�n imp�n que se a distancia entre d�as part�culas � menor  que o raio de 
	corte, a te�amos en conta para a enerx�a potencial, derivadas e aceleraci�ns. Se cumpre a 
	condici�n, sumar� a enerx�a potencial correspondente ao potencial de Lennard - Jones e far�
	o mesmo coas derivadas e fmod. Calc�lanse as aceleraci�ns do seguinte xeito:
	Para a part�cula i (a que estamos considerando) s�maselle a aceleraci�n producida pola par-
	t�cula j, que � fmod*distancia. Como r_ij = - r_ji e fmod � o mesmo, para a part�cula j r�s-
	taselle fmod*distancia porque esta � a aceleraci�n producida pola part�cula i. Ao facer o 
	c�lculo deste xeito e acumular o resultado non � necesario facer que os dous bucles vaian 
	dende 1 ata N.
*/    
    if (D2<=Rc2)
    {
		D2i=1./D2;/*                	   Inversa do m�dulo ao cadrado*/
      	D6=D2i*D2i*D2i;/*          		   Inversa do m�dulo � sexta potencia*/
      	D12=D6*D6;/*               		   Inversa do m�dulo � duod�cima potencia*/
      	*U+=D12-D6;/*              		   Enerx�a potencial*/
      	*phiv-=2.*D12+D6;/*      	       Primeira derivada*/
     	*phivv+=26.*D12-7.*D6;/*           Segunda derivada*/
      	fmod=24.*(2.*D12-D6)*D2i;/*       Parte com�n da forza*/
      	*fx[i]+=fmod*dx;/*     		       Compo�ente x da forza sobre i debida a j*/
      	*fx[j]-=fmod*dx;/*     		       Compo�ente x da forza sobre j debida a i*/
      	*fy[i]+=fmod*dy;/*     		       Compo�ente y da forza sobre i debida a j*/
      	*fy[j]-=fmod*dy;/*     		       Compo�ente y da forza sobre j debida a i*/
      	*fz[i]+=fmod*dz;/*     		       Compo�ente z da forza sobre i debida a j*/
      	*fz[j]-=fmod*dz;/*     		       Compo�ente z da forza sobre j debida a i*/
    }
  }
}
/*
Calculo agora as correcci�ns � enerx�a potencial e as s�as derivadas e introduzo as correcci�ns
nos seus valores. Ter en conta que Rc3 e Rc6 son as inversas da 3� e 6� potencia.
*/
DeltaU=cor*(Rc6/3.-1.)/6.;
*U*=4.;*U+=DeltaU;
Deltaphiv=cor*(1.-2.*Rc6/3.)*L33;
*phiv*=24.*L33;*phiv+=Deltaphiv;
Deltaphivv=cor*(26.*Rc6/3.-7.)*L33;
*phivv*=24.*L33;*phivv+=(Deltaphivv-2.**phiv)*L33;
/*
Fin.
*/
return
}
