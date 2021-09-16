/// 2000. 反转字符前缀

/*
给你一个下标从 0 开始的字符串 word 和一个字符 ch 。找出 ch 第一次出现的下标 i ，反转 word 中从下标 0 开始、直到下标 i 结束（含下标 i ）的那段字符。如果 word 中不存在字符 ch ，则无需进行任何操作。

例如，如果 word = "abcdefd" 且 ch = "d" ，那么你应该 反转 从下标 0 开始、直到下标 3 结束（含下标 3 ）。结果字符串将会是 "dcbaefd" 。
返回 结果字符串 。

输入：word = "abcdefd", ch = "d"
输出："dcbaefd"
解释："d" 第一次出现在下标 3 。 
反转从下标 0 到下标 3（含下标 3）的这段字符，结果字符串是 "dcbaefd" 。
*/
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    string reversePrefix(string word, char ch) {
        string::iterator end = find(word.begin(), word.end(),ch);
        if (end == word.end())
            return word;
        string::iterator start = word.begin();
        while (start < end) {
            swap(*start, *end);
            start++;
            end--;
        }
        return word;
    }
};

int main() {
    Solution solu;
    string word = "abcd";
    char ch = 'z';
    cout << solu.reversePrefix(word, ch)<<endl;

    

    return 0;
}