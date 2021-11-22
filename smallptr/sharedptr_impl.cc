#include<iostream>
#include<mutex>
#include<thread>
using namespace std;

template<class T>
class my_sharedptr{
public:
    /// 对同一个对象使用构造函数实例化一个my_sharedptr, 剩下的用拷贝构造或者赋值操作符来实现。保证引用计数合理
    my_sharedptr(T* ptr) : _ptr(ptr), _refcount(new int(1)), _mtx(new mutex), _isalive(new bool(true)) 
    {}

    ~my_sharedptr() {
        reset();
    }


    /// 用shared_ptr拷贝构造
    my_sharedptr(const my_sharedptr<T>& sp) 
    : _ptr(sp._ptr), 
    _refcount(sp._refcount), 
    _mtx(sp._mtx),
    _isalive(sp._isalive)
    {
        add_ref_count();
    }

    /// operator=() 赋值, 注意类型T一致
    my_sharedptr<T>& operator=(const my_sharedptr<T>& sp) {
        if (_ptr != sp._ptr) {
            /// 删除当前管理的资源
            reset();
            /// 赋新值
            _ptr = sp._ptr;
            _refcount = sp._refcount;
            _mtx = sp._mtx; /// 获取的只是一个指针
            _isalive = sp._isalive;
            /// 增加一个计数
            add_ref_count();
        }
        return *this;
    }


    /// 对shared_ptr的*, ->操作转换为对内部指针的操作
    /// *, 类似于*p, 返回内部指针地址(也就是指针指向的对象的引用)
    T& operator*() {
        return *_ptr;
    }
    T* operator->() {
        return _ptr;
    }


    /// use_count返回计数值
    int use_count() {
        if (!(*_isalive) || !_ptr)    /// 对象已经死亡, 或者已经释放了对象
            return 0;
        return *_refcount;
    }

    /// get()函数返回裸指针
	T* get() { 
        return _ptr; 
    }

    void add_ref_count() {
        std::lock_guard<std::mutex> locker(*_mtx);
        ++(*_refcount);
    }

    //// reset(), 释放当前的shared_ptr, 同时检查释放后引用计数, 如果引用计数为0, 同时删除对象
    /// 注意shared_ptr存储到栈上, 因此不用手动删除shared_ptr
	void reset()
	{
		bool delflag = false;
        {
            /// C/C++中大括号指明了变量的作用域，在大括号内声明的局部变量其作用域自变量声明始，到大括号之后终结。
            std::lock_guard<std::mutex> locker(*_mtx);
            
            if (_refcount > 0 && --(*_refcount) == 0) {
                delete _refcount;
                delete _ptr;    /// 删除对象
                *_isalive = false;
                delflag = true; /// 这里不能删除_mtx, 因为lock_guard使用着
            }
        }
		if (delflag == true)
			delete _mtx;
        /// 重置数据
        _ptr = nullptr;
        _mtx = nullptr;
        _refcount = nullptr;
	}

    void reset(T* ptr) {
        {
            /// C/C++中大括号指明了变量的作用域，在大括号内声明的局部变量其作用域自变量声明始，到大括号之后终结。
            std::lock_guard<std::mutex> locker(*_mtx);
            
            if (_refcount > 0 && --(*_refcount) == 0) {  /// 共享变量计数器减一
                delete _refcount;
                *_isalive = false;
                delete _ptr;    /// 删除对象
            }
        } 
        /// 维护新对象
        _ptr = ptr;
        _refcount =new int(1);
        *_isalive  =true;
    }

private:
	int* _refcount; /// refcount需要用指针, 因为实际的refcount是一个共享变量, 每个shared_ptr对象都存储一个指针指向该共享变量
	T* _ptr;
	mutex* _mtx;    /// mutex和count一样, 也是多线程共享变量
    bool* _isalive;   //_ptr指向的对象是否存活

};

class Person
{
public:
    Person(int v) {
        value = v;
        std::cout << "Cons" <<value<< std::endl;
    }
    ~Person() {
        std::cout << "Des" <<value<< std::endl;
    }

    int value;

};

int main()
{

    
    cout << "shared_ptr test: \n";
    shared_ptr<Person> p1(new Person(1));// Person(1)的引用计数为1

    //my_sharedptr<Person> p2 = std::make_shared<Person>(2);
    cout <<"p1 count: "<< p1.use_count() <<"\n";

    p1.reset(new Person(3));// 首先生成新对象，然后shared_ptr引用计数减1，引用计数为0，故析构Person(1)
                            // 最后将新对象的指针交给智能指针
    cout << "p1 count: "<<p1.use_count() <<"\n";
    shared_ptr<Person> p3 = p1;//现在p1和p3同时指向Person(3)，Person(3)的引用计数为2
    cout << "p1 count: "<<p1.use_count() <<"\n";
    cout << "p3 count: " <<p3.use_count() <<"\n";
    p1.reset();//Person(3)的引用计数为1
    cout << "p1 count: "<<p1.use_count() <<"\n";
    p3.reset();//Person(3)的引用计数为0，析构Person(3)
    cout << "p3 count: " <<p3.use_count() <<"\n";

    /// 
    cout << "p1 count: "<<p1.use_count() <<"\n";
    cout << "p3 count: " <<p3.use_count() <<endl;

    cout << "\nmy_shared_ptr test: \n";
    my_sharedptr<Person> p1_(new Person(1));// Person(1)的引用计数为1

    //my_sharedptr<Person> p2 = std::make_shared<Person>(2);
    cout <<"p1 count: "<< p1_.use_count() <<"\n";

    (*p1_).value = 100;
    cout << "p1 value: " << p1_->value<<"\n";
    p1_.reset(new Person(3));// 首先生成新对象，然后引用计数减1，引用计数为0，故析构Person(1)
                            // 最后将新对象的指针交给智能指针
    cout << "p1 count: "<<p1_.use_count() <<"\n";
    my_sharedptr<Person> p3_ = p1_;//现在p1和p3同时指向Person(3)，Person(3)的引用计数为2
    cout << "p1 count: "<<p1_.use_count() <<"\n";
    cout << "p3 count: " <<p3_.use_count() <<"\n";
    p1_.reset();//Person(3)的引用计数为1
    cout << "p1 count: "<<p1_.use_count() <<"\n";
    p3_.reset();//Person(3)的引用计数为0，析构Person(3)
    cout << "p3 count: " <<p3_.use_count() <<endl;

    /// 对象被析构同时refcount共享变量也被析构, 因此调用use_count时指向的共享变量已经不再存活
    /// 判断共享变量是否存活可以用weak_ptr维护共享变量, 每次访问之前调用lock()尝试提升为shared_ptr, 如果成功说明存活, 最后再reset(). weakptr要求共享变量用shared_ptr维护, 不然提升之后进行reset将析构共享变量
    /// 项目中执行使用weak_ptr的expired()检查use_count是否为0可以判断是否存活,这个必须结合shared_ptr使用
    /// 这里使用一个共享变量isalive判断对象是否存活
    cout << "p1 count: "<<p1_.use_count() <<endl;
    cout << "p3 count: " <<p3_.use_count() <<endl;


    return 0;
}