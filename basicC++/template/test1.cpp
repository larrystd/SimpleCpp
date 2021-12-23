#include <iostream>

using namespace std;

namespace my{
template <typename T>
T add(T a, T b) {
    return a + b;
}
}

namespace my2{
template <typename T, typename N>   // 必须有两个不同类型的模板T, N
T add(T a, T b) {
    return a + b;
}
}


int main() {
    cout << my::add(1,2)<<endl;

    cout << my2::add(2,2)<<endl;


    return 0;
}