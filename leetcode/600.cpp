/// 600. 不含连续1的非负整数

/* 给定一个正整数 n，找出小于或等于 n 的非负整数中，其二进制表示不包含 连续的1 的个数。
输入: 5
输出: 5
解释: 
下面是带有相应二进制表示的非负整数<= 5：
0 : 0
1 : 1
2 : 10
3 : 11
4 : 100
5 : 101
其中，只有整数3违反规则（有两个连续的1），其他5个满足规
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int get_bina_len(int n) {
        for (int i = 31; i >= 0; i--) {
            /// n的二进制有多少位
            if ((n>>i) & 1 == 1)
                return i;
        }
    }

    int findIntegers(int n) {
        int len = get_bina_len(n);
        vector<vector<int>> dp(len+2, vector<int>(2,0));
        dp[1][0] = 1;
        dp[1][1] = 2;
        for (int i = 1; i <= len; i++) {
            dp[i+1][0] = dp[i][1];
            dp[i+1][1] = dp[i][0] + dp[i][1];
        }
        /// 从高到低
        int res = 0;
        int prev = 0;
        for (int i = len; i >= 0; i--) {
            /// 当前位数字
            int cur = (n>>i) &1;
            if (cur == 1)
                /// 当前放0的所有结果
                res += dp[i+1][0];
            /// 不能继续下去因为这里不能放1了
            if (prev == 1 && cur == 1) 
                break; 
            /// 如果没有连续的1说明这里可以继续放1
            prev = cur;
            /// 加一个当前的值
            if (i == 0) res++;

        }
        return res;
    }
};

int main() {
    Solution solu;

    cout << solu.findIntegers(4)<<endl;
    return 0;
}