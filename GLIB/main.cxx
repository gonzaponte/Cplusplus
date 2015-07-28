#include "Vector.h"

int main(void)
{
  //std::cout << "HOLA" << std::endl;
  int s = 10;
  int x[] = {0,1,2,3,4,5,6,7,8,9};
  glib::Vector<int> a( x, s );
  //glib::Vector<int> a( x, x + s );
  glib::Vector<int> b = a;// + 5;
  glib::Vector<int> c;

  a = a / 1;
  b *= 2;
  b = b.Slice(0,s);
  a += 1;
  c = a.Slice(0,s,2);
  a.Swap(0,-1);
  for ( int i=0; i<a.size(); i++ ) std::cout << i << " " << a[i] << " " << b[i] << std::endl;
  for ( int i=1; i<=a.size(); i++ ) std::cout << i << " " << a[-i]<< std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;
  return 0;
}
