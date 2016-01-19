#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main( void )
{
    ofstream a;
    a.open( "proba.bin", ios::binary);
    a << "Hola" << endl;
    int i=10;
    while (i)
    {
        a << setprecision(10) << 1.0/--i << endl;
    }
    a.close();
    return 0;
}