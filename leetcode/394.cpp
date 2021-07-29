/*
给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

原始数据不包含数字，所有的数字只表示重复的次数 k 
输入：s = "3[a]2[bc]"
输出："aaabcbc"

输入：s = "3[a2[c]]"
输出："accaccacc"


逆波兰式（Reverse Polish notation，RPN，或逆波兰记法），也叫后缀表达式（将运算符写在操作数之后）
便于用栈操作

如果当前的字符为数位，解析出一个数字（连续的多个数位）并进栈。注意数字可能是连续的多个数位
如果当前的字符为字母或者左括号，直接进栈
如果当前的字符为右括号，开始出栈，一直到左括号出栈，出栈序列反转后拼接成一个字符串，此时取出栈顶的数字（此时栈顶一定是数字），就是这个字符串应该出现的次数，我们根据这个次数和字符串构造出新的字符串并进栈

可以试试deque模拟queue操作
vector模拟stack操作
*/
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:

    string decodeString(string s) {
        stack<int> sta_digit;    // 储存数字
        stack<char> sta_str;    // 储存字符
        stack<char> sta_help;
        vector<char> list_help;
        string res;
        bool flag;

        for (int i = 0; i < s.size(); ) {
            if (isdigit(s[i])){ // 连续数字
                int j = i;
                while (j < s.size() && isdigit(s[j])){
                    j++;
                }
                sta_digit.push(atoi(s.substr(i,j-i).c_str()));
                i = j;

            }
            else {  // 处理字符
                if (s[i] != ']') {
                    sta_str.push(s[i]);
                    i++;
                } else {
                    char c = sta_str.top();
                    while (c != '[') {
                        list_help.push_back(c);
                        sta_str.pop();
                        c = sta_str.top();
                    }
                    sta_str.pop();  // [出栈
                    int times = sta_digit.top();
                    sta_digit.pop();
                    int len = list_help.size();
                    for (int j = 0; j < times; j++) {
                        for (int k = len-1; k >= 0; k--) {
                            sta_str.push(list_help[k]);
                        }  
                    }
                    list_help.clear();
                    i++;
                }
            }
        }
        while (!sta_str.empty()) {
            res.push_back(sta_str.top());
            sta_str.pop();
        }
        reverse (res.begin(), res.end());
        return res;
    }
};

int main() {
    Solution s;
    cout << s.decodeString("3[a]2[bc]") <<endl;
    return 0;
}