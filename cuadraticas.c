#include <stdio.h>
#include <complex.h>
#include <math.h>
int main(void)
{
    float a, b, c, Delta, inv, root1, root2;
    printf("\nEste programa calcula raices de ecuacions cuadraticas con coeficientes reais.\n");
    printf("\nCoeficiente cuadratico:\n");
    scanf("%f",&a);
    printf("\nCoeficiente lineal:\n");
    scanf("%f",&b);
    printf("\nCoeficiente independente:\n");
    scanf("%f",&c);
    Delta=b*b-4*a*c;
    inv=1/a;inv/=2;
    if (Delta>=0)
    {
       Delta=sqrt(Delta);
       root1=(-b+Delta)*inv;
       root2=(-b-Delta)*inv;
       printf("\nAs raices son:\n");
       printf("\nraiz +: %.4f\n",root1);
       printf("\nraiz -: %.4f\n\n",root2);
    }
    else
    {
        Delta=sqrt(-Delta);
        root1=-b*inv;
        root2= Delta*inv;
        printf("\nAs raices son:\n");
        printf("\nraiz +: %.6f + %.6f i   \n",root1,root2);
        printf("\nraiz -: %.6f - %.6f i \n\n",root1,root2);
    }    
    system("pause");
    return 0;
}
