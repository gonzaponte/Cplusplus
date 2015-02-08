#include <stdio.h>

void main(void)
{
     static int contador;
     printf("contador= %d\n\n",contador++);
     system("pause");
     return;
}
