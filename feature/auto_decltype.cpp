/*
类型推导，引入auto和decltype关键字
这样编译期就推导出变量或者表达式的类型

auto 必须马上初始化
auto不能作函数参数
auto 不能定义数组，但是可以定义指针

decltype用来推导表达式类型
*/

template <typename T, typename U>
decltype(t+u) add (T t, U u) {  // 无法通过编译，t和u类型不确定，因此decltype(t + u)推导出错
    return t + u;
}

// 返回值后置类型语法就是为了解决函数返回值类型依赖于参数难以确定类型的问题
template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
    return t + u;
}