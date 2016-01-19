// This program generates the initial state for a system of N particles in a fcc structure.
// Velocities of particles are randomly determined and therefore momenta is corrected in order
// to move to the rest frame of the system. Values of total momenta are shown before and after
// this correction. Moreover, the kinetic energy is calculated as a sum of the individual ones.
// Potential energy and its first and second derivatives are obtained through the Lennard - Jones
// potential with a cut radius. The error introduced with it is estimated with some corrections
// to those variables. Furthermore, the total acceletation is calculated and shown. Finally,
// the total energy is asked for by screen and fixed. Velocities are re-scaled in order to
// achieve this total energy. The important values of the system situation are recorder to be
// used by the equilibration program.

#include "functions.h"

int main( void )
{
    cout << endl;
    cout << "Number of particles: \t\t" << N << endl;
    cout << "Box size: \t\t\t" << L << endl;
    cout << "Number of cells per dimension:  " << n << endl;
    cout << "Cell size: \t\t\t" << a << endl;
    cout << "Particle density: \t\t" << rho << endl;
    cout << endl;
    
    for ( int k=0; k<n; k++ )
    {
        for ( int j=0; j<n; j++ )
        {
            for ( int i=0; i<n; i++ )
            {
                x.push_back(   i         * a );
                x.push_back( ( i + 0.5 ) * a );
                x.push_back( ( i + 0.5 ) * a );
                x.push_back(   i         * a );
                
                y.push_back(   j         * a );
                y.push_back(   j         * a );
                y.push_back( ( j + 0.5 ) * a );
                y.push_back( ( j + 0.5 ) * a );
                
                z.push_back(   k         * a );
                z.push_back( ( k + 0.5 ) * a );
                z.push_back(   k         * a );
                z.push_back( ( k + 0.5 ) * a );
                
                for ( int ii=0; ii<4; ii++ )
                {
                    vx.push_back( Random() );
                    vy.push_back( Random() );
                    vz.push_back( Random() );
                }
            }
        }
    }
        
    double Px = sumvector( vx );
    double Py = sumvector( vy );
    double Pz = sumvector( vz );
    
    cout << endl << "Value of momenta before correction: \t" << Px << " \t" << Py << "\t" << Pz << endl;
    
    sumtovector( vx, -Px*iN );
    sumtovector( vy, -Py*iN );
    sumtovector( vz, -Pz*iN );
    
    Px = sumvector( vx );
    Py = sumvector( vy );
    Pz = sumvector( vz );
    
    cout << endl << "Value of momenta after correction: \t" << Px << "\t" << Py << "\t" << Pz << endl;
    
    Kinetic();
    
    zeros( fx, N );
    zeros( fy, N );
    zeros( fz, N );
    
    PLJ();
    
    const double Fx = sumvector( fx );
    const double Fy = sumvector( fy );
    const double Fz = sumvector( fz );

    cout << endl << "Total acceleration: \t\t\t" << Fx << "\t" << Fy << "\t" << Fz << endl;
    
    E = K + V;
    
    cout << endl;
    cout << "These are the values of the energies:" <<endl;
    cout << "Total energy: \t\t\t\t" << E << endl;
    cout << "Kinetic energy: \t\t\t" << K << endl;
    cout << "Potential energy: \t\t\t" << V << endl;
    cout << "First derivative of potential energy: \t" << dV << endl;
    cout << "Second derivative of potential energy: " << ddV << endl;
    cout << endl;
    
    cout << endl;
    cout << "Choose total energy (default = 0) \t";
    cin >> E;
    cout << endl;
    
    if ( ( E < V ) || E>=0 )
    {
        E = 200.0 + V ;
        cout << endl;
        cout << "Wrong energy. Using E = " << E << " instead." << endl;
        cout << endl;
    }
    
    const double Kfactor = sqrt( ( E - V ) / K );
    
    scalevector( vx, Kfactor );
    scalevector( vy, Kfactor );
    scalevector( vz, Kfactor );
    
    Kinetic();
    
    cout << endl;
    cout << "These are the new values of the energies:" << endl;
    cout << "Total energy: \t\t\t\t" << E << endl;
    cout << "Kinetic energy: \t\t\t" << K << endl;
    cout << "Potential energy: \t\t\t" << V << endl;
    cout << "First derivative of potential energy: \t" << dV << endl;
    cout << "Second derivative of potential energy: " << ddV << endl;
    cout << endl;
    
    SaveRVA( (char*)"RVA0.dat" );
    SaveEnergies( (char*) "InitialState.dat" );
}