#include <meta_test.h>
#include <iostream>

using namespace std;

// 传入两个类型参数, 该类型参数具有value值, value记录了该占位符表示第N个参数
template<class T1, class T2>
struct tyPlus {
	using type = tyPlus<T1, T2>;
    
    void print() {
        cout << T1::value<<endl;
    }
	const static int value = (T1::value + T2::value);
};

template<class T1, class T2>
struct tyMinus{
	using type = tyMinus<T1, T2>;
	const static int value = (T1::type::value - T2::type::value);
};

template<class T1, class T2>
struct tyMultiple{
	using type = tyMultiple<T1, T2>;
	const static int value = (T1::type::value * T2::type::value);
};

template<class T>
struct tyInverse {
	using type = tyInverse<T>;
	const static int value = -T::type::value;
};

template<int val>
struct _int {
	using type = _int<val>;
	const static int value = val;
	operator int() {
		return value;
	}
};

int main() {
	// 基于占位符, 能够实现填充
    // 用placeholders::_1类型来构造tyPlus
    // 返回类型为lambdaImpl<T>::type
    using tyDouble = tymeta::lambda<tyPlus<tymeta::placeholders::_1, tymeta::placeholders::_2>>::type;
    // 这是设置占位符类型值为24, 调用apply
    cout << tyDouble::apply<_int<24>, _int<22>>::type::value << endl;   // 实例化成tyPlus<_int<24> _int<22>>
    //tyPlus<tymeta::placeholders::_1, tymeta::placeholders::_1> ty;
	// cout << tymeta::lambda<tyPlus<tymeta::placeholders::_1, tymeta::placeholders::_2>>::type::apply<_int<24>, _int<22>>::type::value<<endl;
    //ty.print();
}