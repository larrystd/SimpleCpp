#include <iostream>
#include <string>

using namespace std;

class Person {
public:
    string name;
    int id;
    Person() :name(""), id(0) {}
    Person(string _name, int _id) : name(_name), id(_id) {}

    Person(const Person& person) = default;
    Person& operator=(const Person& person) = default;

    Person(Person&& person) = default;
    Person& operator=(Person&& person) = default;



    friend ostream& operator<<(ostream& out, Person& p);
};

ostream& operator<<(ostream& out, Person& p){
    out << p.name <<" + "<< p.id;
    return out;
}

int main() {

    Person p1("rui", 1);
    Person p2;
    cout << p1 <<"\n";
    p2 = std::move(p1);
    cout << p1 <<"\n";
    cout << p2 <<"\n";
    
    return 0;
}