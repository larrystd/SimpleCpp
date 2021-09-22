#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
using namespace std;

class Person{
public:
    string name;
    int age;

    Person(string n, int a){
        name = n;
        age = a;
    }
	/// 等比比较符, operator==
    bool operator==(const Person & p) const 
    {
        return name == p.name && age == p.age;
    }
};

/// 通过重载operator() 提供hash函数计算
struct hash_name{
	size_t operator()(const Person & p) const{
		/// hash自动实现了散列函数, 返回size_t类型作为散列值
		/// 使用异或, 是实现hash扩散最好的选择
		return hash<string>()(p.name) ^ hash<int>()(p.age);
	}
};

int main(int argc, char* argv[]){
	unordered_map<Person, int, hash_name> ids; //不需要把哈希函数传入构造器
	ids[Person("Mark", 17)] = 40561;
    ids[Person("Andrew",16)] = 40562;
    for (auto&& ii = ids.begin() ; ii != ids.end() ; ii++ )
        cout << ii->first.name 
        << " " << ii->first.age
        << " : " << ii->second
        << endl;
    
    cout << hash<int>()(11) <<endl;
    cout << hash<string>() ("123")<<endl;
    return 0;
}