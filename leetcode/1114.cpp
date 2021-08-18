#include <mutex>
#include <functional>
#include <thread>
#include <iostream>
#include <condition_variable>

using namespace std;



class Foo {
    //mutex mtx1, mtx2;
public:
    Foo() {
        //mtx1.lock(), mtx2.lock();
    }

    void first(function<void()> printFirst) {
        printFirst();
        //mtx1.unlock();
    }

    void second(function<void()> printSecond) {
        //mtx1.lock();
        printSecond();
        //mtx1.unlock();
        //mtx2.unlock();
    }

    void third(function<void()> printThird) {
        //mtx2.lock();
        printThird();
        //mtx2.unlock();
    }
};


class Foo2 {
    mutex mtx_1, mtx_2;
    unique_lock<mutex> lock_1, lock_2;
public:
    Foo2() : lock_1(mtx_1, try_to_lock), lock_2(mtx_2, try_to_lock) {
    }

    void first(function<void()> printFirst) {
        printFirst();
        lock_1.unlock();
    }

    void second(function<void()> printSecond) {
        lock_guard<mutex> guard(mtx_1);
        printSecond();
        lock_2.unlock();
    }

    void third(function<void()> printThird) {
        lock_guard<mutex> guard(mtx_2);
        printThird();
    }


    void start() {
        std::thread t1 (&Foo2::first, this,[]() {
            cout << "first" << endl;
        });

        std::thread t2 (&Foo2::second, this,[]() {
            cout << "second" << endl;
        });

        std::thread t3 (&Foo2::third, this,[]() {
            cout << "third" << endl;
        });

        t1.join();
        t2.join();
        t3.join();
    }
};


class Foo3 {
    condition_variable cv;
    mutex mtx;
    int k = 0;
public:
    void first(function<void()> printFirst) {
        printFirst();
        k = 1;
        cv.notify_all();    // 通知其他所有在等待唤醒队列中的线程
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lock(mtx);   // lock mtx
        cv.wait(lock, [this](){ return k == 1; });  // unlock mtx，并阻塞等待唤醒通知，需要满足 k == 1 才能继续运行
        printSecond();
        k = 2;
        cv.notify_one();    // 随机通知一个（unspecified）在等待唤醒队列中的线程
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lock(mtx);   // lock mtx
        cv.wait(lock, [this](){ return k == 2; });  // unlock mtx，并阻塞等待唤醒通知，需要满足 k == 2 才能继续运行
        printThird();
    }
};


class Test
{
public:

    void testfunc() {
        cout << "call foo::testfunc()" <<endl;
    }
};


int main() {

    Test l;

    auto exp = [](string a) {
        cout << a <<endl;
        cout << "first" <<endl;
    };

    std::thread t1(exp, "kong");

    std::thread t2(&Test::testfunc, l);

    t1.join();
    t2.join();

    /*
    Foo3 foo;
    function<void()> first_f = []() {
        cout << "first" <<endl;
    };
    std::thread t3(&Foo3::first,foo,  first_f);

    t3.join();
    */

   Foo2 foo2;
   foo2.start();
    return 0;
}

