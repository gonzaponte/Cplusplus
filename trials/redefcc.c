#include <stdio.h>
#include <math.h>
#include "potencialLJ"
#define N=500
#define L=10
#define Rc=5
#define pi=3.14159265458979
/*
Introdúcese o programa fcc que prepara as condicións iniciais colocando partículas nun cubo en rede
fcc. Os parámetros de entrada serán os seguintes:

-N:  número de partículas do sistema
-L:  lado do cubo de simulación
-E:  enerxía total do sistema
-Rc: raio de corte do potencial

Declaro variables escalares a usar:

-s,i,x,y,z: variables auxiliares para bucles
-k:         número de celdas por eixo
-ndp:       número de partículas en dobre precisión
-ndpi:      inverso de ndp
-ldp:       lado da caixa de simulación en dobre precisión
-ldpi:      inversa de ldp
-L3:        volume do cubo de simulación
-L33:       inversa do triple do volume
-rho:       densidade de partículas
-kdp:       número de celdas por eixo en dobre precisión
-a:         lado de cada celda
-U:         enerxía potencial total
-phiv:      1ª derivada da enerxía potencial
-phivv:     2ª derivada da enerxía potencial
-T0:        enerxía cinética "aleatoria"
-T:         enerxía cinética real
-E:         enerxía total
-factor:    factor que usarei para reescalar a enerxía cinética
-Px,Py,Pz:  compoñentes do momento total do sistema
-Ax,Ay,Az:  compoñentes da aceleración total do sistema
-Rc2:       raio de corte ao cadrado
-Rc3:       inversa do raio de corte ao cubo
-Rc6:       inversa do raio de corte elevado a seis
-cor:       factor a usar nas correccións da enerxía potencial e as súas derivadas
*/
int s,i,k,x,y,z;
double ndp,ndpi,ldp,ldpi,L3,L33,rho,kdp,a,U,phiv,phivv,T0,T,E,factor,Px,Py,Pz,Ax,Ay,Az;
double Rc2,Rc3,Rc6,cor;
/*
Declaro variables vectoriais a usar:

-rx,ry,rz:        compoñentes dos vectores posición de cada partícula
-vx,vy,vz:        compoñentes dos vectores velocidade de cada partícula
-fx,fy,fz:        compoñentes dos vectores aceleración de cada partícula
-difx,dify,difz:  compoñentes dos vectores de desprazamentos infinitesimais das partículas
*/
double rx[N],ry[N],rz[N],vx[N],vy[N],vz[N],fx[N],fy[N],fz[N],difx[N],dify[N],difz[N];
/*
*/
void main(void)
{
/*
Defino variables que usarei máis adiante.
*/
ndp=double(N);/*                  Número de partículas en dobre precisión*/
ndpi=1./ndp;/*                    Inversa do número de partículas*/
ldp=double(L);/*                  Lado da caixa en dobre precisión*/
ldpi=1./ldp;/*                    Inversa do lado da caixa*/
Rc2=double(Rc*Rc);/*              Raio de corte ao cadrado*/
Rc3=1./(Rc2*double(Rc));/*        Inversa do raio de corte ao cubo*/
Rc6=Rc3*Rc3;/*                    Inversa da sexta potencia do raio de corte*/
/*
Calculo as variables propias da caixa de simulación que usarei no programa:
*/
L3=ldp*ldp*ldp;/*                   Volume*/
rho=ndp*ldpi*ldpi*ldpi;/*           Densidade*/
kdp=pow(0.25*ndp,1./3.);/*          Nº de celdas por eixo en dobre precisión*/
a=ldp/kdp;/*                        Lado da celda*/
k=int(kdp);/*                       Nº de celdas por eixo en formato enteiro*/
/*
Calculo outros factores para usar máis adiante
*/
L33=1./(3.*L3);/*                    =1/3V*/
cor=16.*pi*rho*ndp*Rc3;/*            =16·pi·rho·N/Rc^3*/
/*
Comprobo que os parámetros sexan adecuados.
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
	printf("\n\nErro: o raio de corte non pode ser maior que a metade da caixa de simulación.\n\n");
    system("pause");
    return;
}
/*
Para a composición das coordenadas, collo unha celda e poño partículas en (0,0,0),(a/2,a/2,0),
(a/2,0,a/2) e (0,a/2,a/2). Repito a operación desprazándome por tódolos x's, y's e z's. Polo tanto
as coordenadas das partículas dunha celda calquera son as representadas abaixo. O desprazamento de
calquera coordenada é, obviamente, o tamaño da celda: "a". Os bucles corren no número de celda co-
mezando en 0 para facilitar a asignación de coordenadas. En consecuencia a última celda debe ser a
k-1. As coordenadas das celdas deben ir de 0 ata L-a (última celda) porque a celda situada en x=L,
y=L ou z=L colocaría partículas fóra da caixa.

Defino o índice s que recorrerá tódolos elementos dos vectores posición. Póñoo a cero para
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
Introduzo unha condición de erro por se non se colocaron tódalas partículas.
*/
if (s!=N)
{
  printf("\n\nNon se colocaron tódalas partículas\n");
  printf("   s=',s,'e   N=',N\n\n");
  system("pause");
  return;
}
/*
Agora pretendo mover tódalas partículas unha distancia "infinitesimal" da súa posición inicial de
rede fcc. Para iso creo uns vectores de números pseudo-aleatorios entre 0 e 1.
*/
call random_number(difx);
call random_number(dify);
call random_number(difz);
/*
Agora reescalo estes vectores para que vaian entre -0.001 e 0.001 e desprazo as coordenadas iniciais
nesa cantidade. Canto máis grande sexa a caixa menos significativo será.
*/
rx+=0.001*(2.*difx-1.);
ry+=0.001*(2.*dify-1.);
rz+=0.001*(2.*difz-1.);
/*
A continuación,calculo a enerxía potencial. Para iso chamo á subrutina potencialLJ que devolve 
U,phiv,phivv,fx,fy,fz. A explicación inclúese na subrutina. Anulo os valores para iniciais
*/
U=0.;
phiv=0.;
phivv=0.;
fx=0.;
potencialLJ(&U,&phiv,&phivv,&fx,&fy,&fz);
/*
A continuación realizo a asignación de velocidades aleatorias a cada partícula. Para iso xenero
tres vectores de números pseudo-aleatorios entre 0 e 1 que son as compoñentes das velocidades para
cada partícula.
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
Calculo o momento total que como son variables reducidas non é máis que as sumas de compoñentes da
velocidade.
*/
Px=sum(vx);
Py=sum(vy);
Pz=sum(vz);
/*
Como non será cero (e debe selo), desprazamos as compoñentes das velocidades nunha cantidade igual
á súa media (coincide por ser variables reducidas) para que o momento total sexa nulo. Debe selo
ao ser a colectividade microcanónica e, polo tanto, un sistema illado.
*/
vx-=Px*ndpi;
vy-=Py*ndpi;
vz-=Pz*ndpi;
/*
Calculo a enerxía cinética "aleatoria" resultante
*/
T0=0.5*sum(vx*vx+vy*vy+vz*vz);
/*
Amoso en pantalla os valores obtidos para a enerxía cinética e potencial e pido que se introduza
a enerxía total.
*/
printf("\n\nU= %f\n",U);
printf("\nT= %f\n",T0);
printf("\nInsertar enerxía total do sistema:\n\n");
scanf("%f",&E);
/*
Calculo a nova enerxía cinética e se a enerxía introducida non é adecuada dará un erro.
*/
T=E-U;
if(T<0.)
{
  printf("\n\nErro: enerxía cinética negativa\n\n");
  system("pause");
  return;
}
/*
Reescalo as velocidades mediante as seguintes liñas. Obviamente o momento total segue sendo nulo.
*/
factor=pow(T/T0,0.5);
vx*=factor;
vy*=factor;
vz*=factor;
/*
Calculo o momento (de novo) e a aceleración total:
*/
Px=sum(vx)
Py=sum(vy)
Pz=sum(vz)
Ax=sum(fx)
Ay=sum(fy)
Az=sum(fz)
/*
Amoso en pantalla tódalas variables interesantes da simulación:
*/
printf("\n\nN= %d\n",N);/*                        Número de partículas*/
printf("\na= %f\n",a);/*                          Lado de cada celda*/
printf("\nk= %d\n",k);/*                          Número de celdas por eixo*/
printf("\nrho= %f\n",rho);/*                      Densidade de partículas*/
printf("\nL= %f\n",double L);/*                   Lado da caixa de simulación*/
printf("\nV= %f\n",L3);/*                         Volume da caixa de simulación*/
printf("\nU= %f\n",U);/*                          Enerxía potencial total*/
printf("\ndU/dt= %f\n",phiv);/*                   Primeira derivada da enerxía potencial*/
printf("\ndU2/dt2= %f\n",phivv);/*                Segunda derivada da enerxía potencial*/
printf("\nT= %f\n",T);/*                          Enerxía cinética*/
printf("\nE= %f\n",E);/*                          Enerxía total*/
printf("\n\nP= %f    %f    %f\n",Px,Py,Pz);/*     Momento total*/
printf("\n\nA= %f    %f    %f\n",Ax,Ay,Az);/*     Aceleración total*/
/*
Defino os formatos a usar no gravado de arquivos.
*//*
9000	format(1pe13.6,8(1x,e13.6))
8000	format(1pe19.12,8(1x,e19.12))
8001	format(1pe19.12,4(1x,e19.12))
8002	format(4(i8))
*//*
Gravo en ASCII os vectores de posicións, velocidades e aceleracións
As tres primeiras columnas son x,y,z, as tres seguintes vx,vy,vz e as tres últimas ax,ay,az.
*//*
open(10,file='Matrix.dat')
	do i=1,N
	  write(10,9000) rx(i),ry(i),rz(i),vx(i),vy(i),vz(i),fx(i),fy(i),fz(i)
    enddo
close(10)
*//*
Gravo en binario os vectores de posicións, velocidades e aceleracións.
*//*
open(20,file='Matrixbin.dat',form='unformatted')
	write(20) rx,ry,rz,vx,vy,vz,fx,fy,fz
close(20)
*//*
Gravo en ASCII as variables escalares de interés:
*//*
open(30,file='Números.dat')
	write (30,8002) N,k,L,Rc                           Enteiros
    write (30,8000) ndp,ldp,ldpi,a,rho,L3,Rc2,Rc3,Rc6  Reais 1
	write (30,8001) U,phiv,phivv,T,E                   Reais 2
close(30)
*//*
Fin.
*/
    stop
}
