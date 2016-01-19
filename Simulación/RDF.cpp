#include "functions.h"

int main(void)
{
    zeros( rdf, nbins );
    
    filein.open( "RVAall.dat", ios::in | ios::binary );
    for ( int t=0; t<nrecord; t++ )
    {
        double aux;
        for ( int i=0; i<N; i++ )
        {
            filein.read( (char*) &aux, sizeof( double ) ); x.push_back(aux);
            filein.read( (char*) &aux, sizeof( double ) ); y.push_back(aux);
            filein.read( (char*) &aux, sizeof( double ) ); z.push_back(aux);
            filein.read( (char*) &aux, sizeof( double ) );
            filein.read( (char*) &aux, sizeof( double ) );
            filein.read( (char*) &aux, sizeof( double ) );
            filein.read( (char*) &aux, sizeof( double ) );
            filein.read( (char*) &aux, sizeof( double ) );
            filein.read( (char*) &aux, sizeof( double ) );
        }
        
        for ( int i=0; i<N; i++ )
        {
            const double x0 = x[i];
            const double y0 = y[i];
            const double z0 = z[i];
            
            for ( int j=i+1; j<N; j++ )
            {
                double dx  = x[j] - x0;
                double dy  = y[j] - y0;
                double dz  = z[j] - z0;
                dx -= L * (double) round( dx * iL );
                dy -= L * (double) round( dy * iL );
                dz -= L * (double) round( dz * iL );
                
                const double r2 = dx*dx + dy*dy + dz*dz;
                
                if (r2>rc2)
                    continue;
                
                rdf[ (int)floor( sqrt(r2)*iprecision ) ] += 2;
            }
        }
        
         x.clear();
         y.clear();
         z.clear();        
    }
    filein.close();
    
    scalevector( rdf, idealgas*iN*iprecision3/(double)nrecord );
    
    fileout.open( "RDF.dat", ios::out );
    for ( int i=0; i<nbins; i++ )
    {
        rdf[i] /=  3.0*i*(i+1.0) + 1.0 ;
        fileout << setprecision(16) << rdf[i] << endl;
    }
    fileout.close();

    return 0;
}
