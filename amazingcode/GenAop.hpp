#ifndef __GENERALAOP_H__
#define __GENERALAOP_H__

#include "CppAop.hpp"

class GeneralAop
{
public:
    GeneralAop() = delete;
    ~GeneralAop() = delete;

/// 模板参数类型为一个Function, 一些args.而且很显然AP表示AOP整合的通用类, 比如日志类
/// 参数Function是要执行的函数, 后面Args是参数
    template <typename... AP, typename... Args, typename Function>
    static void invoke(Function &&f, Args &&... args)
    {
        /// 基于要执行的function args生成WzAop对象
        WzAop::CppAop<Function, Args...> asp(std::forward<Function>(f));

        /// asp是构建好的要执行的function, 基于切片类AP调用invoke
        /// WzAop::identity_t 返回AP的类型
        asp.invoke(std::forward<Args>(args)..., WzAop::identity_t<AP>()...);
    }
};

#endif