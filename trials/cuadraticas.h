#include <stdio.h>
#include <complex.h>
#include <math.h>
int main(void)
{
    float a, b, c, Delta, inv, root1, root2;
    printf("\nEste programa calcula raices de ecuacions cuadraticas. Como ainda\n");
    printf("non tenho nin puta idea, so vale para raices reais\n\n");
    printf("\nCoeficiente cuadratico:\n");
    scanf("%f",&a);
    printf("\nCoeficiente lineal:\n");
    scanf("%f",&b);
    printf("\nCoeficiente independente:\n");
    scanf("%f",&c);
    Delta=sqrt(b*b-4*a*c);
    inv=1/a;inv/=2;
    root1=(-b+Delta)*inv;
    root2=(-b-Delta)*inv;
    printf("\nAs raices son:\n");
    printf("\nraiz +: %.4f\n",root1);
    printf("\nraiz -: %.4f\n\n",root2);
    system("PAUSE");
    return 0;
}
