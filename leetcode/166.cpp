/// leetcode 166 分数到小数

/*
给定两个整数，分别表示分数的分子 numerator 和分母 denominator，以 字符串形式返回小数 。

如果小数部分为循环小数，则将循环的部分括在括号内。

如果存在多个答案，只需返回 任意一个 。

对于所有给定的输入，保证 答案字符串的长度小于 104 。

 

示例 1：

输入：numerator = 1, denominator = 2
输出："0.5"
示例 2：

输入：numerator = 2, denominator = 1
输出："2"
示例 3：

输入：numerator = 2, denominator = 3
输出："0.(6)"
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        string res("");
        unordered_map<int, int> str_map;
        int n = numerator / denominator; 
        if (n == 0)
            res.push_back('0');
        while (n) {
            res.push_back('0'+n%10);
            n /= 10;
        }

        int remain = numerator % denominator;
        reverse(res.begin(), res.end());
        if (remain == 0) {
            
            return res;
        }
        
        res.push_back('.');
        int pos = 0;
        string part("");
        while (remain != 0) {
            if (str_map.count(remain)) {
                if (str_map[remain] == 0){
                    res.push_back('(');
                    res.append(part);
                    res.push_back(')');
                    return res;
                }
                int i = 0;
                
                while (part[i] == '0'){
                    res.push_back(part[i]);
                    i++;
                }
                i = 0;
                while (i < str_map.count(remain)) {
                    res.push_back(part[i]);
                    i++;
                }
                res.push_back('(');

                while (i < part.size()) {
                    res.push_back(part[i]);
                    i++;
                }
                res.push_back(')');
                return res;
            }
            str_map[remain] = pos;
            remain *= 10;
            while (remain / denominator == 0) {
                remain *= 10;
                str_map[remain% denominator] = pos;
                part.push_back('0');
            }
            part.push_back(remain/denominator+'0');
            remain = remain%denominator;
            pos++;
        }

        res.append(part);
        return res;
    }
};

int main() {
    Solution solu;
    cout << solu.fractionToDecimal(1,6)<<endl;
    return 0;
}