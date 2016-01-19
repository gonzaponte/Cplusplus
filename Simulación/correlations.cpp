#include "functions.h"

int main( void )
{
    filein.open( "RVAall.dat", ios::in | ios::binary );
    
    zeros( Rcorrelation, ntimes );
    zeros( Vcorrelation, ntimes );
    
    for ( int i=0; i<= nrecord - ntimes; i+= ntimes )
    {
        for ( int j=0; j<ntimes; j++ )
        {
            double aux;
            for ( int k=0; k<N; k++ )
            {
                filein.read( (char*) &aux, sizeof( double ) ); x.push_back(aux);
                filein.read( (char*) &aux, sizeof( double ) ); y.push_back(aux);
                filein.read( (char*) &aux, sizeof( double ) ); z.push_back(aux);
                filein.read( (char*) &aux, sizeof( double ) );vx.push_back(aux);
                filein.read( (char*) &aux, sizeof( double ) );vy.push_back(aux);
                filein.read( (char*) &aux, sizeof( double ) );vz.push_back(aux);
                filein.read( (char*) &aux, sizeof( double ) );
                filein.read( (char*) &aux, sizeof( double ) );
                filein.read( (char*) &aux, sizeof( double ) );
            }
            
            xt.push_back(x);
            yt.push_back(y);
            zt.push_back(z);
            vxt.push_back(vx);
            vyt.push_back(vy);
            vzt.push_back(vz);
            
             x.clear();
             y.clear();
             z.clear();
            vx.clear();
            vy.clear();
            vz.clear();
        }
        
        for ( int j=0; j<N; j++ )
        {            
            const double  x0 =  xt[0][j];
            const double  y0 =  yt[0][j];
            const double  z0 =  zt[0][j];
            const double vx0 = vxt[0][j];
            const double vy0 = vyt[0][j];
            const double vz0 = vzt[0][j];
            
            for ( int k=0; k<ntimes; k++ )
            {
                double dx = xt[k][j] - x0;
                double dy = yt[k][j] - y0;
                double dz = zt[k][j] - z0;
                
                Rcorrelation[k] += dx * dx + dy * dy + dz * dz;
                
                double dv;
                dv  = vxt[k][j] * vx0;
                dv += vyt[k][j] * vy0;
                dv += vzt[k][j] * vz0;
                
                Vcorrelation[k] += dv;
            }
        }
        
         xt.clear();
         yt.clear();
         zt.clear();
        vxt.clear();
        vyt.clear();
        vzt.clear();
    }
    filein.close();
    
    
    scalevector( Rcorrelation, iN*ntimes/(double)nrecord );
    scalevector( Vcorrelation, iN*ntimes/(double)nrecord );
    
    fileout.open("Correlations.dat", ios::out );
    
    for ( int i=0; i<ntimes; i++ )
        fileout << setprecision(16)
                << Rcorrelation[i] << " "
                << Vcorrelation[i] << endl;
    
    fileout.close();
}
