#include <iostream>
#include <boost/coroutine2/all.hpp>

void coroutine_function(boost::coroutines2::coroutine<void>::pull_type & coro_back)
{
    std::cout << "a ";
    coro_back(); // 锚点，返回
    std::cout << "b ";
    coro_back(); //锚点 返回
    std::cout << "c ";
}

int main()
{
    boost::coroutines2::coroutine<void>::push_type coroutine_object(coroutine_function); 	// 创建协程
    std::cout << "1 ";
    coroutine_object(); // 运行协程
    std::cout << "2 ";
    coroutine_object(); // 返回锚点，继续运行协程
    std::cout << "3 ";
    coroutine_object(); // 返回锚点，继续运行协程
    return 0;
}