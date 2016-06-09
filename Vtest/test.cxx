// Example program
#include <iostream>
#include <string>
#include <vector>
#include <memory>

int main()
{
  std::cout << "init" << std::endl;
  class A
  {
  private:
    int x, y, z;
  public:
    A(){}
    A(int xx, int yy, int zz){x=xx;y=yy;z=zz;}
    ~A(){}
    //A(const A& a);
    
    int getX(){return x;}
  };
  std::cout << "creating a" << std::endl;
  std::unique_ptr<std::vector<A>> a,b,c;
  a = std::unique_ptr<std::vector<A>>(new std::vector<A>);
  a->reserve(10);
  
  for (int i=0; i<10; ++i) a->emplace_back(i,i,i);
  
  std::cout << "creating b" << std::endl;
  b = std::make_unique<std::vector<A>>(*a);
  
  for (int i=0; i<10; ++i) std::cout << i << " " << (*a)[i].getX() << " " << (*b)[i].getX() << std::endl;
  
  
  std::cout << "Hi!" << std::endl;
}
