#include <iostream>

template <class T>
class Mumble
{
  public:
    Mumble( T t = 1024 )
      : tt( t )
    {
      if( tt != t )
        throw ex;
    }

  private:
      T tt;
};

int main()
{
  std::cout << "Hello World!" << std::endl;
}