// 下面是一个经典的单例

/*
单例模式
懒汉式
饿汉式

https://redrain.blog.csdn.net/article/details/111327141
*/

#include <mutex>

class Singleton {
public:
// 一个class只能通过GetInstance创建一个对象
    static Singleton* GetInstance() {
        if (!instance_){    // 不存在对象才创建
            std::lock_guard<std::mutex> lock(lock_);    // 通过加锁保证多线程安全
            if (!instance_){
                instance_ = new Singleton();
            }
        }
        return (Singleton* )instance_;
    }
private:
    static std::mutex lock_;
    static volatile Singleton* instance_;

private:
    Singleton() {};
    virtual ~Singleton() {};
    Singleton(const Singleton& ) = delete;
    Singleton& operator=(const Singleton& ) = delete;
};
 
std::mutex Singleton::lock_;
volatile Singleton* Singleton::instance_ = nullptr;
