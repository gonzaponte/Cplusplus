#include <iostream>
#include <cmath>

using namespace std;

class xeometria
{
    class punto;
    class recta;
};
class punto
{
    double x,y,r;
public:
    punto( double x0=0., double y0=0. ){ x=x0; y=y0; r=sqrt( x*x + y*y ); }
    ~punto(){}
    void SetX( double xin ){ x = xin; }
    void SetY( double yin ){ y = yin; }
    double GetX(){ return x; }
    double GetY(){ return y; }
    double GetR();
};

class recta
{
    double m,n;
public:
    recta( double m0=0., double n0=0. ){ m=m0; n=n0; }
    ~recta(){}
    void SetM( double min ){ m = min; }
    void SetN( double nin ){ n = nin; }
    double GetM(){ return m; }
    double GetN(){ return n; }
    double GetXcut(){ return (-n/m); }
    double GetYcut(){ return GetN(); }
    double GetYat( double x0 ){ return ( m*x0 + n ); }
    double GetXat( double y0 ){ return ( (y0-n)/m ); }
    void Create( double x1, double y1, double x2, double y2 );
};

double punto::GetR()
{
    return sqrt( x*x + y*y );
}

void recta::Create( double x1, double y1, double x2, double y2 )
{
    m = (y2-y1)/(x2-x1);
    n = y1-m*x1;
}

void wait (void);

int main ( void )
{
    punto p1(0.,4.), p2(4.,3.);
    recta r1(0.,1.), r2(1.,0.);
    
    //cout << p1.GetX() << "   " << p1.GetY() << "   " << p1.GetR() << endl;
    //cout << p2.GetX() << "   " << p2.GetY() << "   " << p2.GetR() << endl;
    //cout << r1.GetXcut() << endl;
    //cout << r2.GetXcut() << endl;
    
    r1.Create( 0,5,5,0 );
    //cout << r1.GetM() << endl
    //     << r1.GetN() << endl;
    
    int a=0;
    //cout<<a++<<" "<<a<<endl;
    a=1;
    cout<< ++a <<" "<< ++a << " "<< a <<" "<<--a<<endl;
    wait();
    return 0;
}

void wait(void)
{
    cout << "Introduce 0 to finish, 1 to repeat" << endl;
    int a;
    cin >> a;
    if (a) main();
}