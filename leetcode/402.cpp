// 402 移掉k位数字

// 给你一个以字符串表示的非负整数 num 和一个整数 k ，移除这个数中的 k 位数字，使得剩下的数字最小。请你以字符串形式返回这个最小的数字。

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:

    string removeKdigits(string num, int k) {
        // 模拟栈
        if (k == num.size())
            return string("0");
        string stk;
        for (auto& digit: num) {
            while (stk.size() > 0 && stk.back() > digit && k > 0) {
                stk.pop_back();
                k --;
            }
            stk.push_back(digit);
        }

        /// 移除栈元素, 要求k<=num.size()
        for (; k > 0; --k) {
            stk.pop_back();
        }

        string ans = "";
        bool isLeadingZero = true;
        for (auto& digit: stk) {
            if (isLeadingZero && digit == '0') {
                continue;
            }
            isLeadingZero = false;
            ans += digit;
        }
        int i;
        for (i = 0; i < stk.size()-1; i++) {
            if (stk[i] != '0') 
                break;
        }
        return stk.substr(i);
        //return ans == "" ? "0" : ans;
    }

};
int main() {
    Solution s;
    cout << s.removeKdigits("00", 2)<<endl;
    return 0;
}