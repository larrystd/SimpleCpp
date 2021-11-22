#include <memory>
#include <iostream>

using namespace std;

class Widget : public std::enable_shared_from_this<Widget> {
public:
    std::shared_ptr<Widget> GetPtr() {
        //return shared_from_this();  // 这样在已经由shared_ptr<Widget>基础上, 只会让其引用次数+1, 不会产生新的shared_ptr对象维护Widget
        return shared_ptr<Widget>(this);     // 这样导致多个shared_ptr指向对象
    }
};

int main() {
    auto widgett = std::make_shared<Widget>();
    //Widget* ptr = new Widget;
    //ptr->GetPtr();
    widgett->GetPtr();

    return 0;
}