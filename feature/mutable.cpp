/*
const意思是“这个函数不修改对象内部状态”。
mutable意思是“这个成员变量不算对象内部状态”。

例如，用mutable修饰mutex，在于使用empty这个const member function的时候肯定也要先获得内部的一个mutex，
也就是说在const函数时也会改变内部状态，于是就要把mutex_声明成mutable的。
换句话说，获得锁会改变内部状态，故只能把mutex设置为mutable。

设置为mutable的变量一般是类的成员变量，且可以在const成员函数中修改。
*/
#include <string>
class HashTable {
public:
    std::string lookup(const std::string& key) const {
        if (key == last_key_) {
            return last_value_;
        }

        std::string value{this->lookupInternal(key)};

        last_key_ = key;
        last_value_ = value;

        return 0;
    }
private:
    mutable std::string last_key_;  // 设置为mutable，是lookup中可以修改它。但lookup只能修改mutable的变量。
    mutable std::string last_value_;
};