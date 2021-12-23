#include <iostream>
#include <vector>
//#include <type_traits>

using namespace std;

template<class T, T val>
struct constant_val {
	typedef constant_val<T, val> type;
	typedef T value_type;
	constexpr operator value_type() const {
		return value;
	}
	constexpr value_type operator()() const {
		return value;
	}
	static constexpr T value = val;
};

typedef constant_val<bool, true> truetype;
typedef constant_val<bool, false> falsetype;

#define ty_cat(first, second) first##second

template<class T>
struct ty_sfinae_wrapper {
	using type = void;
};

#define ty_has_xxx(member_name) \
template<class T, class U = void> \
struct ty_cat(has_, member_name){ \
	using type = false_type; \
	const static bool value = falsetype::value; \
};\
template<class T> \
struct ty_cat(has_, member_name)<T, typename ty_sfinae_wrapper<typename T::member_name>::type> { \
	using type = true_type;\
	const static bool value = truetype::value;\
};\

ty_has_xxx(iterato);
int main(){
    cout << has_iterato<vector<int>>::value << endl;
    return 0;
}