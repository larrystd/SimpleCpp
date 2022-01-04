/*
给你一个字符数组 chars ，请使用下述算法压缩：

从一个空字符串 s 开始。对于 chars 中的每组 连续重复字符 ：

如果这一组长度为 1 ，则将字符追加到 s 中。
否则，需要向 s 追加字符，后跟这一组的长度。
压缩后得到的字符串 s 不应该直接返回 ，需要转储到字符数组 chars 中。需要注意的是，如果组长度为 10 或 10 以上，则在 chars 数组中会被拆分为多个字符。

请在 修改完输入数组后 ，返回该数组的新长度。

你必须设计并实现一个只使用常量额外空间的算法来解决此问题。


双指针算法

*/

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();

        int i;
        char now = chars[0];
        int count = 1;
        int pos = 0;
        
        for (i = 1; i <= n; i++) {
            if (i<n && chars[i] == chars[pos]) {
                count++;
            }
            else {

                if (count != 1) { // 追加位数
                    
                    int num_digit = 0;
                    string digits = "";
                    while (count) {
                        num_digit++;
                        digits.push_back('0' + count%10);
                        count /= 10;
                    }
                    for (int j = digits.size()-1; j >= 0; j--) {
                        chars[++pos] = digits[j];
                    }
                }
                // 下一个字符     
                if (i < n) {
                    chars[++pos] = chars[i];
                    count = 1;
                }
                                

            }
        }

        return pos+1;
    }
};

int main() {
    Solution s;
    vector<char> chars1 = {'a','a','b','b','c','c','c'};
    vector<char> chars2 = {'a','b','b','b','b','b','b','b','b','b','b','b','b'};
    vector<char> chars3 = {'a'};
    
    cout << s.compress(chars2)<<endl;


    int a = 12;
    char c = 'a';
    int* p1 = &a;
    char* p2 = &c;
    cout << sizeof(p1)<<endl;
    cout << sizeof(p2)<<endl;
    return 0;
}