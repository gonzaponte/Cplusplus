// Este programa admite unha serie de números e ordeaos de xeito ascendente

#include <iostream>
using namespace std;

int main(void)
{
    double x[10],min;
    for (int i=0;i<10;i++)
    {
        if (i==0) cout << "Escribe un número    ";
        else      cout << "Escribe outro número ";
        cin >> x[i];
    }
    for (int i=0;i<10;i++)
    {
        min=x[i];
        for (int j=i+1;j<10;j++)
        {
            if (min>x[j])
            {
            min=x[j];
            x[j]=x[i];
            x[i]=min;
            }
        }
    }
    cout << "\n\n";
    for (int i=0;i<10;i++) cout << x[i] << "  ";
    cout << "\n\n";
    system("pause");
}
