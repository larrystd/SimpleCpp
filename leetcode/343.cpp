/*
整数拆分
给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。

对于的正整数 n，当 n≥2 时，可以拆分成至少两个正整数的和。令 k 是拆分出的第一个正整数，则剩下的部分是 n−k，n−k 可以不继续拆分，或者继续拆分成至少两个正整数的和。

创建数组 dp，其中 dp[i] 表示将正整数 ii 拆分成至少两个正整数的和之后，这些正整数的最大乘积。

0 和 1 都不能拆分，因此dp[0]=dp[1]=0

将 i 拆分成 j 和 i−j 的和，且 i−j 不再拆分成多个正整数，此时的乘积是 j×(i−j)；

将 i 拆分成 j 和 i−j 的和，且 i−j 继续拆分成多个正整数，此时的乘积是 j×dp[i−j]。

*/
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int integerBreak(int n) {
        vector <int> dp(n + 1);

        for (int i = 2; i <= n; i++) {
            int cur_max = 0;
            for (int j = 1; j < i; j++) {
                cur_max = max(cur_max,  max(j * (i - j), j * dp[i - j]));
            }
            dp[i] = cur_max;
        }

        return dp[n];
    }

    
};