//Functions used during all the programs.

#include "variables.h"

template <class T> void print( vector < T > &x, vector < T > &y, vector < T > &z);
void wait( void );
template <class T> void print( T exit );
double Random( void );
template <class T> T sumvector( vector < T > &v );
template <class T> void sumtovector( vector < T > &v, const T t );
template <class T> void scalevector( vector < T > &v, const T t );
void PLJ( void );
template <class T> void zeros( vector < T > &v, const int size );
void Kinetic( void );
void Energy( void);
void Verlet( void );
void SaveEnergies( char *file1 );
void ReadEnergies( char *file1 );
void SaveRVA( char *filename );
void ReadRVA( char *filename );


template <class T > void print( vector < T > &x , vector < T > &y , vector < T > &z )
{
    for ( int i=0; i<x.size(); i++ )
        cout << x[i] << "  "
             << y[i] << "  "
             << z[i] << endl;
}


template <class T> void print( T exit )
{
    cout << endl
         << exit
         << endl;
}

void wait(void)
{
    cout << "Press enter to continue" << endl;
    cin.ignore(255, '\n');
}

double Random (void)
{
    return ( 2.0*r.doub() - 1. );
}

template <class T> T sumvector( vector < T > &v)
{
    T sum = 0;
    for ( int i=0; i<v.size(); i++ )
        sum += v[i];
    
    return sum;
}

template <class T> void sumtovector( vector < T > &v, const T t )
{
    for ( int i=0; i<v.size(); i++ )
        v[i] += t;
}

template <class T> void scalevector( vector < T > &v, const T t )
{
    for ( int i=0; i<v.size(); i++ )
        v[i] *= t;
}


void PLJ( void )
{
    V = 0.0; dV = 0.0; ddV = 0.0;
    scalevector( fx, 0. );
    scalevector( fy, 0. );
    scalevector( fz, 0. );
    
    for ( int i=0; i<N; i++ )
    {
        const double x0 = x[i];
        const double y0 = y[i];
        const double z0 = z[i];
        for ( int j=i+1; j<N; j++ )
        {
            double dx = x0 - x[j];
            double dy = y0 - y[j];
            double dz = z0 - z[j];
            
            dx -= L * (double) round( dx * iL );
            dy -= L * (double) round( dy * iL );
            dz -= L * (double) round( dz * iL );
            
            const double r2 = dx * dx
                            + dy * dy
                            + dz * dz ;
            
            if ( r2 > rc2 )
                continue;
            
            const double ir2 = 1./r2;
            const double ir6 = ir2 * ir2 * ir2;
            const double ir12 = ir6 * ir6;
            const double fmod = 24. * ( 2.*ir12 - ir6 ) * ir2;
            
              V +=     ir12 -    ir6;
             dV += -2.*ir12 +    ir6;
            ddV += 26.*ir12 - 7.*ir6;
            
            fx[i] += fmod * dx;
            fx[j] -= fmod * dx;
            fy[i] += fmod * dy;
            fy[j] -= fmod * dy;
            fz[i] += fmod * dz;
            fz[j] -= fmod * dz;
        }
    }
    
    V *= 4.0;
    V += deltaV;
    
    dV *= 24.0;
    dV += deltadV;
    dV *= iL3_3;
    
    ddV *= 24.0;
    ddV += deltaddV;
    ddV *= iL3_3;
    ddV -= 2.0 * dV;
    ddV *= iL3_3;
}

template <class T> void zeros( vector < T > &v, int size )
{
    for ( int i=0; i<size; i++ )
        v.push_back( 0.0 );
}


void Kinetic( void )
{
    K = 0.0;
    for ( int i=0; i<N; i++ )
        K += vx[i] * vx[i] + vy[i] * vy[i] + vz[i] * vz[i];
    
    K *= 0.5;
}

void SaveEnergies( char *file1 )
{
    fileout.open( file1, ios::out );
    
    fileout << setprecision(16)
            <<   E << endl
            <<   K << endl
            <<   V << endl
            <<  dV << endl
            << ddV << endl;
    
    fileout.close();
}

void ReadEnergies( char *file1 )
{
    filein.open( file1, ios::in );

    filein >>   E;
    filein >>   K;
    filein >>   V;
    filein >>  dV;
    filein >> ddV;

    filein.close();
}

void Verlet( void )
{    
    for ( int i=0; i<N; i++ )
    {
         x[i] +=  vx[i]*dt + fx[i]*t22;
         y[i] +=  vy[i]*dt + fy[i]*t22;
         z[i] +=  vz[i]*dt + fz[i]*t22;
        vx[i] +=  fx[i]*t12;
        vy[i] +=  fy[i]*t12;
        vz[i] +=  fz[i]*t12;
    }
    
    PLJ();
    
    for ( int i=0; i<N; i++ )
    {
        vx[i] += fx[i]*t12;
        vy[i] += fy[i]*t12;
        vz[i] += fz[i]*t12;
    }
}

void SaveRVA( char *filename )
{
    fileout.open( filename, ios::out | ios::binary );

    for ( int i=0; i<N; i++ )
    {
        fileout.write( (char*)  &x[i], sizeof( double ) );
        fileout.write( (char*)  &y[i], sizeof( double ) );
        fileout.write( (char*)  &z[i], sizeof( double ) );
        fileout.write( (char*) &vx[i], sizeof( double ) );
        fileout.write( (char*) &vy[i], sizeof( double ) );
        fileout.write( (char*) &vz[i], sizeof( double ) );
        fileout.write( (char*) &fx[i], sizeof( double ) );
        fileout.write( (char*) &fy[i], sizeof( double ) );
        fileout.write( (char*) &fz[i], sizeof( double ) );
    }
    fileout.close();
}

void ReadRVA( char *filename )
{
    filein.open( filename, ios::in | ios::binary );
    double aux;
    for ( int i=0; i<N; i++ )
    {
        filein.read( (char*) &aux, sizeof( double ) ); x.push_back(aux);
        filein.read( (char*) &aux, sizeof( double ) ); y.push_back(aux);
        filein.read( (char*) &aux, sizeof( double ) ); z.push_back(aux);
        filein.read( (char*) &aux, sizeof( double ) );vx.push_back(aux);
        filein.read( (char*) &aux, sizeof( double ) );vy.push_back(aux);
        filein.read( (char*) &aux, sizeof( double ) );vz.push_back(aux);
        filein.read( (char*) &aux, sizeof( double ) );fx.push_back(aux);
        filein.read( (char*) &aux, sizeof( double ) );fy.push_back(aux);
        filein.read( (char*) &aux, sizeof( double ) );fz.push_back(aux);
    }
    filein.close();
}

