#include <iostream>
#include <map>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::stringstream;


class MemoryLeakDetect{
public:
    static MemoryLeakDetect& instance(){
        static MemoryLeakDetect detect;
        return detect;
    }
    void insert(void* ptr, const char* file, int line){
        char ss[50];
        snprintf(ss,50, "%s%d", file, line);
        cout << ss<<endl;
        record[ptr] = ss;  // 放到记录中
    }
    void erase(void* ptr){
        record.erase(ptr);
    }
    void print(){
        for(auto pair : record){    // 剩余的记录为没有被free的内存
            cout<<pair.second<<" memory leakage"<<endl;
        }
    }
private:
    MemoryLeakDetect(){
    }
    map<void*, string> record;
};
void* operator new(std::size_t size, const char* file, int line) {
    cout<<"new"<<size<<endl;
    void* ptr = malloc(size);
    MemoryLeakDetect::instance().insert(ptr, file, line);
    return ptr;
}
void operator delete(void* ptr){
    free(ptr);
    MemoryLeakDetect::instance().erase(ptr);
    ptr = nullptr;
}

#define new new(__FILE__, __LINE__)

class A{
public:
    A(){
        cout<<"construct"<<endl;
    }
    ~A(){
        cout<<"destruct"<<endl;
    }
};
int main(){
    int* p1 = new int;
    A* a1 = new A;
    delete p1;
    delete a1;
    MemoryLeakDetect::instance().print();
    return 0;
}