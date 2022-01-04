#include <set>
#include <map>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class MinStack {
public:
    MinStack() {
    }
    
    void push(int val) {
        minstack.push(val);
        tables[val] ++;
    }
    
    void pop() {
        int temp = minstack.top();
        minstack.pop();
        if (tables[temp] > 1)
            tables[temp] --;
        else
            tables.erase(temp);
        
    }
    
    int top() {
        return minstack.top();
    }
    
    int getMin() {
        return (*tables.begin()).first;
    }
private:
    stack<int> minstack;
    map<int, int> tables;
};

int main() {
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout <<minStack.getMin();   //--> 返回 -3.
    minStack.pop();
    cout <<minStack.top();      //--> 返回 0.
    cout << minStack.getMin() ;  // --> 返回 -2.

    return 0;
}