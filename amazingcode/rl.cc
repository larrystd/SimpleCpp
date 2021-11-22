#include <iostream>
#include <string>

using namespace std;

class Person {
public:
    string name;
    int id;
    Person() :name(""), id(0) {}
    Person(string _name, int _id) : name(_name), id(_id) {}

    Person(const Person& p) {
        name = p.name;
        id = p.id;
    }
    Person& operator=(const Person& p) {
        name = p.name;
        id = p.id;
        return *this;
    }

    Person(Person&& person)
    {
        name = std::move(person.name);
        id = std::move(person.id);
        std::cout << "移动构造函数"<< std::endl;
    }

    Person& operator=(Person&& person){
    if (this != &person)
    {
        name = std::move(person.name);
        id = std::move(person.id);
        std::cout << "移动赋值函数"<< std::endl;
    }
    return *this;
    }



    friend ostream& operator<<(ostream& out, Person& p);
};

ostream& operator<<(ostream& out, Person& p){
    out << p.name <<" + "<< p.id;
    return out;
}

Person&& addid(Person& person) {
    person.id++;
    return std::move(person);
}

string&& addid(string str) {
    str += "123";
    return str;
}

int main() {
    cout << "start" <<"\n";
    string s1("s1");
    string s2("s2");

    s2 = std::move(s1);
    string s3 = s2;
    cout << s1 <<endl;
    cout << s2 <<endl;
    cout << s3<<endl;


    char* c1 = "123";
    cout << c1 << "\n";
    char* c2 = std::move(c1);
    cout << c1 << "\n";
    cout << c2 << "\n";

    Person p1("rui", 1);
    Person p2;
    cout << p1 <<"\n";
    p2 = std::move(p1);
    cout << p1 <<"\n";
    cout << p2 <<"\n";

    cout << addid(std::move(s1))<<endl;
    
    return 0;
}