#include "functions.h"


int main( void )
{
    ReadRVA( (char*) "RVA0.dat" );
        
    int step=0;
    while ( step++ < steps )
    {
        Verlet();
        if ( ! ( step % record ) )
        {
            Kinetic();
            E = K + V;
            
            const double t = dt * (double)step;
            fileout.open( "EKV.dat", ios::app );
            fileout << setprecision(16)
                    << t << " "
                    << E << " "
                    << K << " " 
                    << V << endl;
            fileout.close();
            
            if ( step < 0.5*steps )
                continue;
            
            fileout.open( "RVAall.dat", ios::app | ios::binary );
            
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
    }
    
    SaveEnergies( (char*) "EquilibriumState.dat" );
    SaveRVA( (char*)"RVA1.dat" );
    
    return 0;
}
