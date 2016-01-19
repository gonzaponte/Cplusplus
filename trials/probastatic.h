#include <stdio.h>
void contar()
{
     static int contador=0;
     printf("\n\ncontador= %d\n\n",contador++);
     return;
}
