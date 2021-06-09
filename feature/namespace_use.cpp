#include <iostream>

using namespace std;

int main(){
    int a = 2;
    {
        int a = 3;
        cout<<a<<endl;
    }
    cout << a<<endl;
    return 0;
}

