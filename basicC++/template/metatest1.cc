#include <stdio.h>
#include <type_traits>
using namespace std;

class cool{
public:
  cool(){ printf("Cool!\n");  }
};

class notcool{
public:
  notcool(){ printf("Not cool!\n");  }
};

template<int N>
class myclass{
public:
  typedef typename std::conditional<N==5,cool,notcool>::type thetype;
  thetype theinst;
};

int main(){
  printf("Testing\n");
  myclass<5> myc5;
  myclass<6> myc6;
  printf("Done testing\n");
  return 0; 
} 