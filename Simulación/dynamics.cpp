#include "functions.h"


int main( void )
{
    ReadRVA( (char*)"RVA1.dat" );

    zeros( T     , times);
    zeros( Cv    , times);
    zeros( P     , times);
    zeros( alphaE, times);
    zeros( Gamma , times);
    zeros( kS    , times);
    
    const int stepsitimes = steps*itimes;
    
    for (int i=0; i<times; i++)
    {
            Kmean = 0.0;
           iKmean = 0.0;
            Vmean = 0.0;
           dVmean = 0.0;
          ddVmean = 0.0;
         dViKmean = 0.0;
        dV2iKmean = 0.0;
        
        int step=0;
        while ( step++ < stepsitimes )
        {
            Verlet();
            Kinetic();
            
            const double iK    = 1./K;
            const double dViK  = dV * iK;
            const double dV2iK = dV * dViK;
            
                Kmean +=     K;
               iKmean +=    iK;
                Vmean +=     V;
               dVmean +=    dV;
              ddVmean +=   ddV;
             dViKmean +=  dViK;
            dV2iKmean += dV2iK;
        }
        
        const double normfactor = 1./(double)stepsitimes;
            Kmean *= normfactor;
           iKmean *= normfactor;
            Vmean *= normfactor;
           dVmean *= normfactor;
          ddVmean *= normfactor;
         dViKmean *= normfactor;
        dV2iKmean *= normfactor;
    
             T[i]  = 2.0*Kmean*idof;
            Cv[i]  = (2.0*idof-1.0)*Kmean*iKmean;
            Cv[i] += 1.0;
            Cv[i]  = 1.0/Cv[i];
             P[i]  = N*T[i]*iL3;
             P[i] -= dVmean;
        alphaE[i]  = (1.0-2.0*idof)*Kmean*dViKmean;
        alphaE[i] -= dVmean;
        alphaE[i] *= L3;
        alphaE[i]  = 1.0/alphaE[i];
         Gamma[i]  = N/Cv[i];
         Gamma[i] += L3*(0.5*dof-1.0)*(dVmean*iKmean-dViKmean);
            kS[i]  = dV2iKmean-2.0*dVmean*dViKmean;
            kS[i] += iKmean*dVmean*dVmean;
            kS[i] *= L3*(0.5*dof-1.0);
            kS[i] -= N*T[i]*iL3*(1.0+2*Gamma[i]-N/Cv[i])+L3*ddVmean;
            kS[i]  = -1.0/kS[i];
    }
    
    E = V + K;
    
    SaveEnergies( (char*)"EquilibriumState2.dat" );
    SaveRVA( (char*)"RVA2.dat" );
    
         Tmean = sumvector(    T   ) * itimes;
        Cvmean = sumvector(   Cv   ) * itimes;
         Pmean = sumvector(    P   ) * itimes;
    alphaEmean = sumvector( alphaE ) * itimes;
     Gammamean = sumvector(  Gamma ) * itimes;
        kSmean = sumvector(   kS   ) * itimes;
    
    for (int i=0; i<5; i++)
    {
        sT      += (     T[i] -      Tmean ) * (     T[i] -      Tmean );
        sCv     += (    Cv[i] -     Cvmean ) * (    Cv[i] -     Cvmean );
        sP      += (     P[i] -      Pmean ) * (     P[i] -      Pmean );
        salphaE += (alphaE[i] - alphaEmean ) * (alphaE[i] - alphaEmean );
        sGamma  += ( Gamma[i] -  Gammamean ) * ( Gamma[i] -  Gammamean );
        skS     += (    kS[i] -     kSmean ) * (    kS[i] -     kSmean );
    }
    
    const double itimes2 = itimes/(double)(times-1);
    
    sT       = sqrt( sT      * itimes2 );
    sCv      = sqrt( sCv     * itimes2 );
    sP       = sqrt( sP      * itimes2 );
    salphaE  = sqrt( salphaE * itimes2 );
    sGamma   = sqrt( sGamma  * itimes2 );
    skS      = sqrt( skS     * itimes2 );
    
    fileout.open("Constants.dat", ios::out );
    fileout << setprecision(16)
            <<      Tmean << " " << sT      << " " <<      sT/Tmean      << endl
            <<     Cvmean << " " << sCv     << " " <<     sCv/Cvmean     << endl
            <<      Pmean << " " << sP      << " " <<      sP/Pmean      << endl
            << alphaEmean << " " << salphaE << " " << salphaE/alphaEmean << endl
            <<  Gammamean << " " << sGamma  << " " <<  sGamma/Gammamean  << endl
            <<     kSmean << " " << skS     << " " <<     skS/kSmean     << endl;
    fileout.close();
    
    return 0;
}
