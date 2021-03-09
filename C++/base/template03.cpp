#include <iostream>

template <class Type>
class Point
{
  public:
    enum Status { unallocated, normalized };

    Point( Type x = 0.0, Type y = 0.0, Type z = 0.0 )
      : _x( x ), _y( y ), _z( z ) { }
    ~Point() { }
   
    void* operator new( size_t size ) { return ::operator new( size ); }
    void operator delete( void* pointee ) { ::operator delete( pointee ); } 
    Type y() { return _y; }
    // ...

  public:
    static Point<Type> *freeList;
    static int chunkSize; 
    Type _x, _y, _z;
};

int main()
{
  Point<float> *ptr = 0;
  
  const Point<float> &ref = 0;

  Point<float> *p = new Point<float>;

  Point<int> pi;

  Point<long> pl;

  std::cout << "sizeof( *ptr ) = " << sizeof( *ptr ) << std::endl;

  std::cout << "ptr->_x = " << ptr->_x << std::endl; 
  
  std::cout << "sizeof( ref ) = " << sizeof( ref ) << std::endl;

  std::cout << "ref._x = " << ref._x << std::endl;

  std::cout << " &pi = " << &pi << std::endl;

  std::cout << " &pl = " << &pl << std::endl;
}