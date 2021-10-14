#ifndef __CPPAOP_H__
#define __CPPAOP_H__

#include <iostream>

namespace CppAop {

/*  std::declval返回一个类型的右值引用, 并可以访问模板类的成员函数

std::is_same
位于头文件<type_traits>中, 两个一样的类型会返回true
bool isInt = std::is_same<int, int>::value; //为true

value是 = std::is_same<decltype(check<T>(0)), std::true_type>::value   , 也就是decltype(check<T>(0))类型和std::true_type是否相等

check的模板参数为U, 其实就是输入判定的类型参数为int, 返回类型为decltype(std::declval<U>().member(std::declval<Args>()...), std::true_type())
member会被before或after替代

decltype(std::declval<U>().member(std::declval<Args>()...), std::true_type())输入两个参数, 当std::declval<U>().member(std::declval<Args>()...)有效时会输出std::true_type()

struct A {              // abstract class
  virtual int value() = 0;
};
 
class B : public A {    // class with specific constructor
  int val_;
public:
  B(int i,int j):val_(i*j){}
  int value() {return val_;}
};
 
int main() {
  decltype(std::declval<A>().value()) a;  // int a
  decltype(std::declval<B>().value()) b;  // int b
  decltype(B(0,0).value()) c;   // same as above (known constructor)
*/

#define HAS_MEMBER(member)                                                                                       \
    template <typename T, typename... Args>                                                                      \
    struct HasMember_##member                                                                                    \
    {                                                                                                            \
    private:                                                                                                     \
        template <typename U>                                                                                 \
        static auto check(int) -> decltype(std::declval<U>().member(std::declval<Args>()...), std::true_type()); \
                                                                                                                 \
        template <typename U>                                                                                    \
        static std::false_type check(...);                                                                       \
                                                                                                                 \
    public:                                                                                                      \
        enum                                                                                                     \
        {                                                                                                        \
            value = std::is_same<decltype(check<T>(0)), std::true_type>::value                                   \
        };                                                                                                       \
    };
}

namespace WzAop
{

#define HAS_MEMBER(member)                                                                                       \
    template <typename T, typename... Args>                                                                      \
    struct HasMember_##member                                                                                    \
    {                                                                                                            \
    private:                                                                                                     \
        template <typename U>                                                                                    \
        static auto check(int) -> decltype(std::declval<U>().member(std::declval<Args>()...), std::true_type()); \
                                                                                                                 \
        template <typename U>                                                                                    \
        static std::false_type check(...);                                                                       \
                                                                                                                 \
    public:                                                                                                      \
        enum                                                                                                     \
        {                                                                                                        \
            value = std::is_same<decltype(check<T>(0)), std::true_type>::value                                   \
        };                                                                                                       \
    };

    /// 宏定义将解折叠, 形成HasMember_before和HasMember_after
    HAS_MEMBER(before)
    HAS_MEMBER(after)

    template <typename Function, typename... Args>
    class CppAop
    {
    public:
        CppAop() = default;

        /// 拷贝函数被delete
        CppAop(const CppAop &) = delete;
        CppAop &operator=(const CppAop &) = delete;

        /// 用Function赋值给m_func
        CppAop(Function &&f) : m_func(std::forward<Function>(f))
        {
        }

        /// std::enable_if 满足条件时类型有效。
        /// 只有HasMember_before<T, Args...>::value && HasMember_after<T, Args...>::value都为true有效, 显然基于宏定义
        /// value = std::is_same<decltype(check<T>(0)), std::true_type>::value, value是bool型
        /// type std::enable_if<>::type, 
        /// type	either T or no such member, depending on the value of B
        /*
        template<bool B, class T = void>
        struct enable_if {};

        template<class T>
        struct enable_if<true, T> { typedef T type; };
        */  
       /// invoke接受切片类并执行之(aspect.before) 
       /// m_func是已经提前赋值的执行函数
        template <typename T>
        typename std::enable_if<HasMember_before<T, Args...>::value && HasMember_after<T, Args...>::value>::type
        invoke(Args &&... args, T &&aspect)
        {
            aspect.before(std::forward<Args>(args)...);
            m_func(std::forward<Args>(args)...);
            aspect.after(std::forward<Args>(args)...);
        }

        /// aspect是输入的参数, 类型是T的通用引用
        /// Args &&... args 是可被before, m_func等函数执行的参数
        template <typename T>
        typename std::enable_if<HasMember_before<T, Args...>::value && !HasMember_after<T, Args...>::value>::type
        invoke(Args &&... args, T &&aspect)
        {
            aspect.before(std::forward<Args>(args)...);
            m_func(std::forward<Args>(args)...);
        }

        template <typename T>
        typename std::enable_if<!HasMember_before<T, Args...>::value && HasMember_after<T, Args...>::value>::type
        invoke(Args &&... args, T &&aspect)
        {
            m_func(std::forward<Args>(args)...);
            aspect.after(std::forward<Args>(args)...);
        }

        template <typename Head, typename... Tail>
        void invoke(Args &&... args, Head &&headAspect, Tail &&... tailAspect)
        {
            headAspect.before(std::forward<Args>(args)...);
            invoke(std::forward<Args>(args)..., std::forward<Tail>(tailAspect)...);
            headAspect.after(std::forward<Args>(args)...);
        }

    private:
        Function m_func;
    };

    /* Cross platform deal: compatibility for visual studio & g++ */
    template <typename T>
    using identity_t = T;

} /* namespace WzAop */

#endif