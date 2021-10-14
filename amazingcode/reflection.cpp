#include <map>
#include <iostream>
#include <string>
using namespace std;


/// 函数指针的typedef
typedef void* (*PTRCreateObject)(void);  

class ClassFactory {
private:  
    map<string, PTRCreateObject> m_classMap ;  
	ClassFactory(){}; //构造函数私有化
	
public:   
    void* getClassByName(string className);  
    void registClass(string name, PTRCreateObject method) ;  
    static ClassFactory& getInstance() ;  
};

void* ClassFactory::getClassByName(string className){  
    map<string, PTRCreateObject>::const_iterator iter;  
    iter = m_classMap.find(className) ;  
    if ( iter == m_classMap.end() )  
        return NULL ;  
    else  
        return iter->second() ;  
}  

/// 注册实例到class_map中, 可以通过字符串调用之
/// 注册的是一个对象获取函数PTRCreateObject, 而不是对象
/// 对象知道使用getClassByName, 将PTRCreateObject强制转换成TestClass才会调用之
/// 显然以上运行时才产生对象, 且根据string获取对象, 反射规则
/// 这种可以实现类似动态的来了一个连接创建对象, 关闭连接释放对象, 不用一开始保留很多对象。因此在spring类似web框架应用广泛
void ClassFactory::registClass(string name, PTRCreateObject method){  
    m_classMap.insert(pair<string, PTRCreateObject>(name, method)) ;  
}  
   
ClassFactory& ClassFactory::getInstance(){
    /// 静态对象, 返回静态对象的引用
    static ClassFactory sLo_factory;  
    return sLo_factory ;  
}  

class RegisterAction{
public:
	RegisterAction(string className,PTRCreateObject ptrCreateFn){
        printf("ok2\n");
        /// 调用ClassFactory, 获取工厂实例,调用registClass注册之     
		ClassFactory::getInstance().registClass(className,ptrCreateFn);
	}
};


/*
#表示字符串化操作符（stringification）。其作用是：将宏定义中的传入参数名转换成用一对双引号括起来参数名字符串。
##表示连接 
*/
#define REGISTER(className) 											\
	className* objectCreator##className(){     							\
    printf("ok\n");     \
        return new className;                                         	\
    }                                                                   \
    RegisterAction g_creatorRegister##className(                        \
		#className,(PTRCreateObject)objectCreator##className)   ///(#className,(PTRCreateObject)objectCreator##className) 初始化一个RegisterAction对象
    /// 注意这里只是将函数作为参数用来构造RegisterAction实例

// test class
class TestClass{
public:
	void m_print(){
		cout<<"hello TestClass"<<endl;
	};
};
REGISTER(TestClass);

int main(int argc,char* argv[]) {
	TestClass* ptrObj=(TestClass*)ClassFactory::getInstance().getClassByName("TestClass");
	//ptrObj->m_print();
}
