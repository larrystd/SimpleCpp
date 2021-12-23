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

	typedef constant_val<bool, true> true_type;
	typedef constant_val<bool, false> false_type;

        #define ty_cat(first, second) first##second

	template<class T>
	struct ty_sfinae_wrapper {
		using type = void;
	};

	#define ty_has_xxx(member_name) \
	template<class T, class U = void> \
	struct ty_cat(has_, member_name){ \
		using type = false_type; \
		const static bool value = false_type::value; \
	};\
	template<class T> \
	struct ty_cat(has_, member_name)<T, typename ty_sfinae_wrapper<typename T::member_name>::type>{\
		using type = true_type;\
		const static bool value = true_type::value;\
	};\

	ty_has_xxx(type)

	template<unsigned int N>
	struct arg {
		const static unsigned int value = N;
	};

	template<unsigned int N, class firstArg, class ...trueArgs>
	struct getArg {
		using type = typename getArg<N - 1, trueArgs...>::type;
	};

	template<class firstArg, class ...Args>
	struct getArg<1, firstArg, Args...> {
		using type = firstArg;
	};

	template<class T, class ...trueArgs>
	struct lambdaImpl {
		using type = T;
	};

	template<
		unsigned int N,
		class ...trueArgs
	>
	struct lambdaImpl<arg<N>, trueArgs...>{
		using type = typename getArg<N, trueArgs...>::type;
	};

	template<
		template<class ...Args> class T,
		class ...Args,
		class ...trueArgs
	>
	struct lambdaImpl<T<Args...>, trueArgs...> {
		using type = typename lambdaImpl<T<Args...>>::type::template apply<trueArgs...>::type;
	};
		

	template<
		template<class ...Args> class T,
		class ...Args
	>
	struct lambdaImpl<T<Args...>>{
		struct type {
			template<class A, class U>
			struct apply_aux{};
			template<class U>
			struct apply_aux<true_type, U>{
				using type = typename U::type;
			};
			template<class U>
			struct apply_aux<false_type, U>{
				using type = U;
			};
			template<class ...trueArgs>
			struct apply {
				using solved_type = T< typename lambdaImpl<Args, trueArgs...>::type... >;
				using type = typename apply_aux<typename has_type<solved_type>::type, solved_type>::type;	// 
			};
		};
	};


	template<class T>	// T是一个函数
	struct lambda {
		using type = typename lambdaImpl<T>::type;
	};

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