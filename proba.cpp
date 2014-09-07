#include <iostream>

// Usamos el espacio std
using namespace std;

float cuadrado( const float s ) { return s * s; }

int main( )
{
cout << "Introduce un número para calcular su cuadrado: ";
float num;
cin >> num;
cout << "El cuadrado de " << num << " es " << cuadrado( num ) << "n";
return 0;
} 
