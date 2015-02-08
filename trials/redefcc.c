#include <stdio.h>
#include <math.h>
#include "potencialLJ"
#define N=500
#define L=10
#define Rc=5
#define pi=3.14159265458979
/*
Introd�cese o programa fcc que prepara as condici�ns iniciais colocando part�culas nun cubo en rede
fcc. Os par�metros de entrada ser�n os seguintes:

-N:  n�mero de part�culas do sistema
-L:  lado do cubo de simulaci�n
-E:  enerx�a total do sistema
-Rc: raio de corte do potencial

Declaro variables escalares a usar:

-s,i,x,y,z: variables auxiliares para bucles
-k:         n�mero de celdas por eixo
-ndp:       n�mero de part�culas en dobre precisi�n
-ndpi:      inverso de ndp
-ldp:       lado da caixa de simulaci�n en dobre precisi�n
-ldpi:      inversa de ldp
-L3:        volume do cubo de simulaci�n
-L33:       inversa do triple do volume
-rho:       densidade de part�culas
-kdp:       n�mero de celdas por eixo en dobre precisi�n
-a:         lado de cada celda
-U:         enerx�a potencial total
-phiv:      1� derivada da enerx�a potencial
-phivv:     2� derivada da enerx�a potencial
-T0:        enerx�a cin�tica "aleatoria"
-T:         enerx�a cin�tica real
-E:         enerx�a total
-factor:    factor que usarei para reescalar a enerx�a cin�tica
-Px,Py,Pz:  compo�entes do momento total do sistema
-Ax,Ay,Az:  compo�entes da aceleraci�n total do sistema
-Rc2:       raio de corte ao cadrado
-Rc3:       inversa do raio de corte ao cubo
-Rc6:       inversa do raio de corte elevado a seis
-cor:       factor a usar nas correcci�ns da enerx�a potencial e as s�as derivadas
*/
int s,i,k,x,y,z;
double ndp,ndpi,ldp,ldpi,L3,L33,rho,kdp,a,U,phiv,phivv,T0,T,E,factor,Px,Py,Pz,Ax,Ay,Az;
double Rc2,Rc3,Rc6,cor;
/*
Declaro variables vectoriais a usar:

-rx,ry,rz:        compo�entes dos vectores posici�n de cada part�cula
-vx,vy,vz:        compo�entes dos vectores velocidade de cada part�cula
-fx,fy,fz:        compo�entes dos vectores aceleraci�n de cada part�cula
-difx,dify,difz:  compo�entes dos vectores de desprazamentos infinitesimais das part�culas
*/
double rx[N],ry[N],rz[N],vx[N],vy[N],vz[N],fx[N],fy[N],fz[N],difx[N],dify[N],difz[N];
/*
*/
void main(void)
{
/*
Defino variables que usarei m�is adiante.
*/
ndp=double(N);/*                  N�mero de part�culas en dobre precisi�n*/
ndpi=1./ndp;/*                    Inversa do n�mero de part�culas*/
ldp=double(L);/*                  Lado da caixa en dobre precisi�n*/
ldpi=1./ldp;/*                    Inversa do lado da caixa*/
Rc2=double(Rc*Rc);/*              Raio de corte ao cadrado*/
Rc3=1./(Rc2*double(Rc));/*        Inversa do raio de corte ao cubo*/
Rc6=Rc3*Rc3;/*                    Inversa da sexta potencia do raio de corte*/
/*
Calculo as variables propias da caixa de simulaci�n que usarei no programa:
*/
L3=ldp*ldp*ldp;/*                   Volume*/
rho=ndp*ldpi*ldpi*ldpi;/*           Densidade*/
kdp=pow(0.25*ndp,1./3.);/*          N� de celdas por eixo en dobre precisi�n*/
a=ldp/kdp;/*                        Lado da celda*/
k=int(kdp);/*                       N� de celdas por eixo en formato enteiro*/
/*
Calculo outros factores para usar m�is adiante
*/
L33=1./(3.*L3);/*                    =1/3V*/
cor=16.*pi*rho*ndp*Rc3;/*            =16�pi�rho�N/Rc^3*/
/*
Comprobo que os par�metros sexan adecuados.
*/
if ((rho>1.)||(rho<0.1))
{
	printf("\n\nErro: a densidade toma un valor extremo.\n\n");
    system("pause");
    return;
}
if ((kdp-double(k))>0.001)
{
 	 printf("\n\nErro: N debe ser da forma N=4k^3.\n\n");
 	 system("pause");
 	 return;
}
if (double(Rc)>0.5*ldp)
{
	printf("\n\nErro: o raio de corte non pode ser maior que a metade da caixa de simulaci�n.\n\n");
    system("pause");
    return;
}
/*
Para a composici�n das coordenadas, collo unha celda e po�o part�culas en (0,0,0),(a/2,a/2,0),
(a/2,0,a/2) e (0,a/2,a/2). Repito a operaci�n despraz�ndome por t�dolos x's, y's e z's. Polo tanto
as coordenadas das part�culas dunha celda calquera son as representadas abaixo. O desprazamento de
calquera coordenada �, obviamente, o tama�o da celda: "a". Os bucles corren no n�mero de celda co-
mezando en 0 para facilitar a asignaci�n de coordenadas. En consecuencia a �ltima celda debe ser a
k-1. As coordenadas das celdas deben ir de 0 ata L-a (�ltima celda) porque a celda situada en x=L,
y=L ou z=L colocar�a part�culas f�ra da caixa.

Defino o �ndice s que recorrer� t�dolos elementos dos vectores posici�n. P��oo a cero para
que comece no elemento 1.
*/
s=0;
do z=0,k-1
    do y=0,k-1
        do x=0,k-1
            s++;
            rx(s)=x*a;
            ry(s)=y*a;
            rz(s)=z*a;
            s++;
            rx(s)=(x+0.5)*a;
            ry(s)=(y+0.5)*a;
            rz(s)=z*a;
            s++;
            rx(s)=(x+0.5)*a;
            ry(s)=y*a;
            rz(s)=(z+0.5)*a;
            s++;
            rx(s)=x*a;
            ry(s)=(y+0.5)*a;
            rz(s)=(z+0.5)*a;
        enddo
    enddo
enddo
/*
Introduzo unha condici�n de erro por se non se colocaron t�dalas part�culas.
*/
if (s!=N)
{
  printf("\n\nNon se colocaron t�dalas part�culas\n");
  printf("   s=',s,'e   N=',N\n\n");
  system("pause");
  return;
}
/*
Agora pretendo mover t�dalas part�culas unha distancia "infinitesimal" da s�a posici�n inicial de
rede fcc. Para iso creo uns vectores de n�meros pseudo-aleatorios entre 0 e 1.
*/
call random_number(difx);
call random_number(dify);
call random_number(difz);
/*
Agora reescalo estes vectores para que vaian entre -0.001 e 0.001 e desprazo as coordenadas iniciais
nesa cantidade. Canto m�is grande sexa a caixa menos significativo ser�.
*/
rx+=0.001*(2.*difx-1.);
ry+=0.001*(2.*dify-1.);
rz+=0.001*(2.*difz-1.);
/*
A continuaci�n,calculo a enerx�a potencial. Para iso chamo � subrutina potencialLJ que devolve 
U,phiv,phivv,fx,fy,fz. A explicaci�n incl�ese na subrutina. Anulo os valores para iniciais
*/
U=0.;
phiv=0.;
phivv=0.;
fx=0.;
potencialLJ(&U,&phiv,&phivv,&fx,&fy,&fz);
/*
A continuaci�n realizo a asignaci�n de velocidades aleatorias a cada part�cula. Para iso xenero
tres vectores de n�meros pseudo-aleatorios entre 0 e 1 que son as compo�entes das velocidades para
cada part�cula.
*/
call random_number(vx)
call random_number(vy)
call random_number(vz)
/*
Coas seguintes ordes reescalo as velocidades para que vaian de -1 a 1.
*/
vx=2.*vx-1.;
vy=2.*vy-1.;
vz=2.*vz-1.;
/*
Calculo o momento total que como son variables reducidas non � m�is que as sumas de compo�entes da
velocidade.
*/
Px=sum(vx);
Py=sum(vy);
Pz=sum(vz);
/*
Como non ser� cero (e debe selo), desprazamos as compo�entes das velocidades nunha cantidade igual
� s�a media (coincide por ser variables reducidas) para que o momento total sexa nulo. Debe selo
ao ser a colectividade microcan�nica e, polo tanto, un sistema illado.
*/
vx-=Px*ndpi;
vy-=Py*ndpi;
vz-=Pz*ndpi;
/*
Calculo a enerx�a cin�tica "aleatoria" resultante
*/
T0=0.5*sum(vx*vx+vy*vy+vz*vz);
/*
Amoso en pantalla os valores obtidos para a enerx�a cin�tica e potencial e pido que se introduza
a enerx�a total.
*/
printf("\n\nU= %f\n",U);
printf("\nT= %f\n",T0);
printf("\nInsertar enerx�a total do sistema:\n\n");
scanf("%f",&E);
/*
Calculo a nova enerx�a cin�tica e se a enerx�a introducida non � adecuada dar� un erro.
*/
T=E-U;
if(T<0.)
{
  printf("\n\nErro: enerx�a cin�tica negativa\n\n");
  system("pause");
  return;
}
/*
Reescalo as velocidades mediante as seguintes li�as. Obviamente o momento total segue sendo nulo.
*/
factor=pow(T/T0,0.5);
vx*=factor;
vy*=factor;
vz*=factor;
/*
Calculo o momento (de novo) e a aceleraci�n total:
*/
Px=sum(vx)
Py=sum(vy)
Pz=sum(vz)
Ax=sum(fx)
Ay=sum(fy)
Az=sum(fz)
/*
Amoso en pantalla t�dalas variables interesantes da simulaci�n:
*/
printf("\n\nN= %d\n",N);/*                        N�mero de part�culas*/
printf("\na= %f\n",a);/*                          Lado de cada celda*/
printf("\nk= %d\n",k);/*                          N�mero de celdas por eixo*/
printf("\nrho= %f\n",rho);/*                      Densidade de part�culas*/
printf("\nL= %f\n",double L);/*                   Lado da caixa de simulaci�n*/
printf("\nV= %f\n",L3);/*                         Volume da caixa de simulaci�n*/
printf("\nU= %f\n",U);/*                          Enerx�a potencial total*/
printf("\ndU/dt= %f\n",phiv);/*                   Primeira derivada da enerx�a potencial*/
printf("\ndU2/dt2= %f\n",phivv);/*                Segunda derivada da enerx�a potencial*/
printf("\nT= %f\n",T);/*                          Enerx�a cin�tica*/
printf("\nE= %f\n",E);/*                          Enerx�a total*/
printf("\n\nP= %f    %f    %f\n",Px,Py,Pz);/*     Momento total*/
printf("\n\nA= %f    %f    %f\n",Ax,Ay,Az);/*     Aceleraci�n total*/
/*
Defino os formatos a usar no gravado de arquivos.
*//*
9000	format(1pe13.6,8(1x,e13.6))
8000	format(1pe19.12,8(1x,e19.12))
8001	format(1pe19.12,4(1x,e19.12))
8002	format(4(i8))
*//*
Gravo en ASCII os vectores de posici�ns, velocidades e aceleraci�ns
As tres primeiras columnas son x,y,z, as tres seguintes vx,vy,vz e as tres �ltimas ax,ay,az.
*//*
open(10,file='Matrix.dat')
	do i=1,N
	  write(10,9000) rx(i),ry(i),rz(i),vx(i),vy(i),vz(i),fx(i),fy(i),fz(i)
    enddo
close(10)
*//*
Gravo en binario os vectores de posici�ns, velocidades e aceleraci�ns.
*//*
open(20,file='Matrixbin.dat',form='unformatted')
	write(20) rx,ry,rz,vx,vy,vz,fx,fy,fz
close(20)
*//*
Gravo en ASCII as variables escalares de inter�s:
*//*
open(30,file='N�meros.dat')
	write (30,8002) N,k,L,Rc                           Enteiros
    write (30,8000) ndp,ldp,ldpi,a,rho,L3,Rc2,Rc3,Rc6  Reais 1
	write (30,8001) U,phiv,phivv,T,E                   Reais 2
close(30)
*//*
Fin.
*/
    stop
}
