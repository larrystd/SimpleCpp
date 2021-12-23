#include <iostream>
#include <type_traits>
 
// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename std::enable_if<std::is_integral<T>::value,bool>::type  // 前部分为true是, 才有第二个成员, 也就是bool
 is_odd (T i) {return bool(i%2);}
 
// 2. the second template argument is only valid if T is an integral type:
template < class T,
      class = typename std::enable_if<std::is_integral<T>::value>::type>    // std::is_integral<T>::value>为ture才有T成员, type是传入的模板参数
bool is_even (T i) {return !bool(i%2);}
 
int main() {
 
 short int i = 1;  // code does not compile if type of i is not integral
 
 std::cout << std::boolalpha;
 std::cout << "i is odd: " << is_odd("ss") << std::endl;
 std::cout << "i is even: " << is_even(i) << std::endl;
 
 return 0;
}