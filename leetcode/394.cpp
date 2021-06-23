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
*/
#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<int> sta_digit;
        stack<int> sta_alp;
        string res;
        bool flag;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] >= '0' && s[i] <=)
        }
    }
};