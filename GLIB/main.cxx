#include "Vector.h"

int main(void)
{
  std::cout << "HOLA" << std::endl;
  unsigned int s = 10;
  int x[] = {0,1,2,3,4,5,6,7,8,9};
  glib::Vector<int> a( s, x );
  glib::Vector<int> b( s, 2 );
  glib::Vector<int> c = a;// + 5;

  std::cout << "a:                  " << a                  << std::endl;
  std::cout << "b:                  " << b                  << std::endl;
  std::cout << "c:                  " << c                  << std::endl;
  std::cout << "a+2:                " << a+2                << std::endl;
  std::cout << "b-2:                " << b-2                << std::endl;
  std::cout << "c*2:                " << c*2                << std::endl;
  std::cout << "a/2:                " << a/2                << std::endl;
  std::cout << "b+c:                " << b+c                << std::endl;
  std::cout << "b-c:                " << b-c                << std::endl;
  std::cout << "b*c:                " << b*c                << std::endl;
  std::cout << "c/b:                " << c/b                << std::endl;
  std::cout << "a.Slice(0,4):       " << a.Slice(0,4)       << std::endl;
  std::cout << "a.Slice(-11,9,-1):  " << a.Slice(-11,9,-1)  << std::endl; a.Swap(0,-1);
  std::cout << "a.Swap(0,-1):       " << a                  << std::endl;
  std::cout << "a.Reverse:          " << a.Reverse()        << std::endl; a[0] = 110;
  std::cout << "a[0] = 110:         " << a                  << std::endl;
  std::cout << "b.Concatenate(c):   " << b.Concatenate(c)   << std::endl;
  std::cout << "b.Sum():            " << b.Sum()            << std::endl;
  std::cout << "b.Mod():            " << b.Mod()            << std::endl;
  std::cout << "b.Mod2():           " << b.Mod2()           << std::endl;
  std::cout << "b.Dot(b):           " << b.Dot(b)           << std::endl;
  std::cout << "b.Slice(0,1).Pop(): " << b.Slice(0,1).Pop() << std::endl;

  unsigned int nr = 4, nc = 4;
  int m[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
  glib::Vector<int> d( nr, nc, 5 );
  glib::Vector<int> e( nr, nc, m );
  glib::Vector<int> f = a;// + 5;
  glib::Vector<int> d;



  return 0;
}
