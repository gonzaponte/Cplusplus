#include <stdio.h>
/*
*/
void potencialLJ(double *U,double *phiv,double *phivv,double *fx,double *fy,double *fz)
{
/*
A subrutina potencialLJ calcula a enerxía potencial dun sistema, a súa primeira e segunda derivada
e a aceleración resultante a partir do número de partículas, o lado da caixa o raio de corte e as
posicións iniciais.

Declaro variables a usar dentro da subrutina:
-i,j: 		  variables auxiliares para correr nos bucles
-dx,dy,dz:    compoñentes do vector distancia entre dúas partículas
-D2: 		  módulo ao cadrado dese vector
-D2i: 		  inverso do anterior
-D6: 		  inversa da sexta potencia da distancia
-D12:  	      inversa da duodécima potencia da distancia.
-fmod: 	      parte común escalar dos vectores de aceleración.
-DeltaU: 	  corrección á enerxía potencial
-Deltaphiv:   corrección á suma da primeira derivada da enerxía potencial
-Deltaphivv:  corrección á suma da segunda derivada da enerxía potencial
*/
int i,j;
double dx,dy,dz,D2,D2i,D6,D12,fmod,DeltaU,Deltaphiv,Deltaphivv;
/*
Corro o bucle en i dende un ata N-1 e en j de i+1 ata N para non calcular
dúas veces o mesmo.
*/
do i=1,N-1
{
   do j=i+1,N
   {
/*
	Resto os vectores de cada par de partículas.
*/    
    dx=rx[i]-rx[j];
    dy=ry[i]-ry[j];
    dz=rz[i]-rz[j];
/*
	As seguintes liñas redefinen a distancia cunha partícula como a da súa imaxe máis próxima.
*/    
    dx-=ldp*round(dx*ldpi);
	dy-=ldp*round(dy*ldpi);
	dz-=ldp*round(dz*ldpi);
/*
	Calculo o módulo ao cadrado e as inversas do módulo á sexta e a duodécima potencia.
*/    
    D2=dx*dx+dy*dy+dz*dz;
/*
	A seguinte condición impón que se a distancia entre dúas partículas é menor  que o raio de 
	corte, a teñamos en conta para a enerxía potencial, derivadas e aceleracións. Se cumpre a 
	condición, sumará a enerxía potencial correspondente ao potencial de Lennard - Jones e fará
	o mesmo coas derivadas e fmod. Calcúlanse as aceleracións do seguinte xeito:
	Para a partícula i (a que estamos considerando) súmaselle a aceleración producida pola par-
	tícula j, que é fmod*distancia. Como r_ij = - r_ji e fmod é o mesmo, para a partícula j rés-
	taselle fmod*distancia porque esta é a aceleración producida pola partícula i. Ao facer o 
	cálculo deste xeito e acumular o resultado non é necesario facer que os dous bucles vaian 
	dende 1 ata N.
*/    
    if (D2<=Rc2)
    {
		D2i=1./D2;/*                	   Inversa do módulo ao cadrado*/
      	D6=D2i*D2i*D2i;/*          		   Inversa do módulo á sexta potencia*/
      	D12=D6*D6;/*               		   Inversa do módulo á duodécima potencia*/
      	*U+=D12-D6;/*              		   Enerxía potencial*/
      	*phiv-=2.*D12+D6;/*      	       Primeira derivada*/
     	*phivv+=26.*D12-7.*D6;/*           Segunda derivada*/
      	fmod=24.*(2.*D12-D6)*D2i;/*       Parte común da forza*/
      	*fx[i]+=fmod*dx;/*     		       Compoñente x da forza sobre i debida a j*/
      	*fx[j]-=fmod*dx;/*     		       Compoñente x da forza sobre j debida a i*/
      	*fy[i]+=fmod*dy;/*     		       Compoñente y da forza sobre i debida a j*/
      	*fy[j]-=fmod*dy;/*     		       Compoñente y da forza sobre j debida a i*/
      	*fz[i]+=fmod*dz;/*     		       Compoñente z da forza sobre i debida a j*/
      	*fz[j]-=fmod*dz;/*     		       Compoñente z da forza sobre j debida a i*/
    }
  }
}
/*
Calculo agora as correccións á enerxía potencial e as súas derivadas e introduzo as correccións
nos seus valores. Ter en conta que Rc3 e Rc6 son as inversas da 3ª e 6ª potencia.
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
