/// 两整数之和
/*
给你两个整数 a 和 b ，不使用 运算符 + 和 - ​​​​​​​，计算并返回两整数之和。

 

示例 1：

输入：a = 1, b = 2
输出：3
示例 2：

输入：a = 2, b = 3
输出：5
 

提示：

-1000 <= a, b <= 1000
*/
#include <vector>

using namespace std;


class Solution {
public:
    int getSum(int a, int b) {
        int a_left_bit = 0;
        int b_left_bit = 0;
        
        for (int i = 31; i >= 0; i--) {
            if (a & (1 << i)) {
                a_left_bit = i;
                break;
            }
        }
        for (int i = 31; i >= 0; i--) {
            if (b & (1 << i)) {
                b_left_bit = i;
                break;
            }
        }
        int result = 0;
        
        for (int a_bit = a_left_bit, b_bit = b_left_bit; a _bit>=0 && b_bit >=0; a_bit--, b_bit--) {
            int i = a>> a_bit;
            int j = b >> b_bit;
        }
    }
};