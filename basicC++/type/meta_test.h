#pragma once
namespace tymeta {

    typedef unsigned int size_t;

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
		using type = falsetype; \
		const static bool value = falsetype::value; \
	};\
	template<class T> \
	struct ty_cat(has_, member_name)<T, typename ty_sfinae_wrapper<typename T::member_name>::type>{\
		using type = truetype; \	
		const static bool value = truetype::value;\
	};\

	ty_has_xxx(type)

	// 参数, 模板参数不是类型, 而是常量。并且设置const static value = N
	template<unsigned int N>
	struct arg {
		const static unsigned int value = N;
	};

	// 通过递归的方式得到每个arg的type
	// 注意getArg<1>和getArg<2>是两种类型
	template<unsigned int N, class firstArg, class ...trueArgs>
	struct getArg {
		using type = typename getArg<N - 1, trueArgs...>::type;
	};

	template<class firstArg, class ...Args>
	struct getArg<1, firstArg, Args...> {
		using type = firstArg;
	};

	// 定义模板, 可变参数args可以为0
	template<class T, class ...trueArgs>
	struct lambdaImpl {
		using type = T;
	};
	
	// 传入N, 参数args
	template<
		unsigned int N,
		class ...trueArgs
	>
	struct lambdaImpl<arg<N>, trueArgs...>{
		// type是getArg<N>的类型
		using type = typename getArg<N, trueArgs...>::type;
	};	

	template<
		template<class ...Args> class T,
		class ...Args
	>
	struct lambdaImpl<T<Args... >>{
		struct type {

			template<class A, class U>
			struct apply_aux{};

			template<class U>
			struct apply_aux<truetype, U>{
				using type = typename U::type;
			};
			
			template<class U>
			struct apply_aux<falsetype, U>{
				using type = U;
			};


			template<class ...trueArgs>
			struct apply {
				using solved_type = T< typename lambdaImpl<Args, trueArgs...>::type... >;	// 可以解析得到每个args的type tymeta::lambdaImpl<tyPlus<tymeta::arg<1>, tymeta::arg<2> > >, 放置value

				using type = typename apply_aux<typename has_type<solved_type>::type, solved_type>::type;	// has_type<solved_type>::type解析solved_type里有type, 返回true_type
			};
		};
	};


	template<class T>
	struct lambda {
		using type = typename lambdaImpl<T>::type;
	};

	// arg<1> 是一个arg类型, 包括_1, _2都是类型
	namespace placeholders {
		typedef arg<1> _1;
		typedef arg<2> _2;
		typedef arg<3> _3;
		typedef arg<4> _4;
		typedef arg<5> _5;
		typedef arg<6> _6;
		typedef arg<7> _7;
		typedef arg<8> _8;
		typedef arg<9> _9;
		typedef arg<10> _10;
	}
}