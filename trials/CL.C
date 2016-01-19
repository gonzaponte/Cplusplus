///////////////////////////////////////////////////////////////////////////////
// Computation of the confidence level from Chi-squared (chi2)
// and number of constraints (ncons).
//
// Note :
// for even ncons ==> same result as the Cernlib function PROB
// for odd  ncons ==> confidence level < result of the Cernlib function PROB
//
//--- Original Fortan routine copied from Lau Gatignon 1980
//--- Modified by NvE 29-sep-1980 K.U. Nijmegen
//--- Modified by NvE 24-apr-1985 NIKHEF-H Amsterdam
//--- Converted to C++ by Nve 06-nov-1998 UU-SAP Utrecht
//////////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <cstdlib>
#include <iostream>

using namespace std;



float CL(float chi2,int ncons)
{
 const float a1=0.705230784e-1, a2=0.422820123e-1,
             a3=0.92705272e-2,  a4=0.1520143e-3,
             a5=0.2765672e-3,   a6=0.430638e-4;

 // Change to dummy variables
 int    n = ncons;
 float y0 = chi2;

 // Set CL to zero in case ncons<=0
 if (n <= 0)
    return 0;

 if (!y0)
    return 1;
 
 if (y0<0)
    return 0;

 if (n > 100)
 {
  float x    = sqrt(2.*y0) - sqrt( 2.*n - 1. );
  float t    = fabs(x) / 1.1412135;
  float vfun = 1.0 + t * ( a1 + t * ( a2 + t * ( a3 + t * ( a4 + t * ( a5 + t * a6 ) ) ) ) ) ;

  vfun = 1.0 / vfun;
     
  if ( fabs(vfun) < 1.3e-5 ) // Prevent underflow
     vfun=0.;
     
  vfun = pow( vfun, 16 );
  float v = 0.5 * vfun;

  if (x < 0.)
     v = 1.-v;
     
  if (v < 0.)
     v = 0.;
     
  return v;
 }
    
 else
 {
  float y1 = 0.5*y0;
  int    m = n / 2;
     
  if ( 2 * m == n)
  {
   float sum = 1.;
   if (m > 1)
   {
    float term = 1.;
       
    for (int i=2; i<=m; i++)
    {
     if (term > 1.e20)  // Prevent overflow
        break;
        
     float fi = 1.0/(i-1);
     term *= y1 * fi;
     sum  += term;
    }
       
   } 
    float rnick = y1;
      
    if (rnick >= 1.75e2) // Prevent underflow
      rnick=1.75e2;
    
    float v = sum * exp(-rnick);
    if (v < 0.)
      v = 0.;
      
    return v;
  }
     
  else
  {
   float x     = sqrt(y0);
   float t     = fabs(x) / 1.1412135;
   float vfun = 1.0 + t * ( a1 + t * ( a2 + t * ( a3 + t * ( a4 + t * ( a5 + t * a6 ) ) ) ) );

   vfun  = 1.0 / vfun;
      
   if (fabs(vfun) < 1.3e-5) // Prevent underflow
      vfun = 0.;
      
   vfun = pow( vfun, 16 );
      
   float v = vfun;
   if (n < 1)
      return 0;
      
   if (n == 1)
   {
    if (v < 0.)
       v=0.;
    return v;
   }
      
   float value = v;
   float sum = 1.;
      
   if (n >= 4)
   {
    float term = 1.;
    int k = m - 1;
       
    for (int j=1; j<=k; j++)
    {
     if (term > 1.e20) // Prevent overflow
        break;
        
     term *= y0 / ( 2.0 * j + 1.);
     sum  += term;
    }
       
   }
      
   if (y1 > 1.75e2) // Prevent underflow
      y1=1.75e2;
      
   float vi = sum * 0.797846 * sqrt(y0) * exp(-y1);
      
   v = vi + value;
   if (v < 0.)
      v = 0.;
      
   return v;
  }
     
 }
    
}


int main(){
  cout << conlev(1,2)<<endl;
}
