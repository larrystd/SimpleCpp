#include <iostream>
#include <typeinfo>

using namespace std;

template <int A, int B>
struct tyPlus {
    enum class t{
        value = A + B
    };
};

template <int A, int B>
auto tyPlus2() -> decltype(1+1) {
    return A + B;
};

int main() {
    std::is_same
    printf("%d\n",  tyPlus2<2,3>());
    cout << typeid(tyPlus2<2,3>()).name()<<endl;
    cout << typeid(decltype(1+1)).name()<<endl;
}