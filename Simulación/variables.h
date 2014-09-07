#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "nr3.h"
#include "ran.h"

#define pi 3.14159265358979

using namespace std;

const int             n  = 5;
const double          L  = 10.0;
const double         iL  = 1.0 / L;
const double          L3 = L * L * L;
const double         iL3 = 1.0 / L3;
const double          a  = L / (double) n;
const int             N  = 4 * n * n * n;
const double         iN  = 1.0 / (double) N;
const double         rho = (double) N * iL3;
const double         rc  = 0.5 * L;
const double         rc2 = rc * rc;
const double        irc3 = 1.0 / ( rc * rc2 );
const double        irc6 = irc3 * irc3;
const double        corr = 16.0 * pi * rho * (double) N * irc3;
const double      deltaV = corr * ( irc6 / 3.0 - 1.0 ) / 6.0;
const double     deltadV = corr * ( 1.0 - 2.0 * irc6/3.0 );
const double    deltaddV = corr * ( 26.0 * irc6 / 3.0 - 7.0 );
const double       iL3_3 = iL3 / 3.0;
const int          steps = 2000000;
const double      isteps = 1.0/(double)steps;
const int         record = 100;
const int        nrecord = steps/(2*record);
const double          dt = 0.0001;
const double         t12 = 0.5 * dt;
const double         t22 = t12 * dt;
const int         times  = 5;
const double     itimes  = 1.0/(double)times;
const double     itimes2 = itimes/(double)(times-1);
const int        ntimes  = 300;
const double    intimes  = 1.0/(double)ntimes;
const double         dof = 3.0*(double)(N-1);
const double        idof = 1./dof;
const double  precision  = 0.01;
const double iprecision  = 1.0/precision;
const double iprecision3 = iprecision*iprecision*iprecision;
const double       nbins = L*iprecision - 0.5;
const double    idealgas = 3.0/(4.0*pi*rho);
Ran r(9);

vector < double > x,y,z,vx,vy,vz,fx,fy,fz;
vector < vector < double > > xt,yt,zt,vxt,vyt,vzt;

double   E = 0;
double   K = 0;
double   V = 0;
double  dV = 0;
double ddV = 0;

ofstream fileout;
ifstream filein;

double     Kmean;
double    iKmean;
double     Vmean;
double    dVmean;
double   ddVmean;
double  dViKmean;
double dV2iKmean;

vector < double > T,Cv,P,alphaE,Gamma,kS;

double Tmean;
double Cvmean;
double Pmean;
double alphaEmean;
double Gammamean;
double kSmean;

double sT=0;
double sCv=0;
double sP=0;
double salphaE=0;
double sGamma=0;
double skS=0;

vector < double > rdf;
vector < double > Rcorrelation;
vector < double > Vcorrelation;

