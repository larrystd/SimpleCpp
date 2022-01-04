// leetcode309, 最佳买卖股票时机含冷冻期

/*
给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。​

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

输入: [1,2,3,0,2]
输出: 3 
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]

某时刻末三个状态(被决策所影响的三个状态), 
1. 持有股票
2. 未持有股票在冷冻期
3. 未持有股票但不再冷冻期

f[i][j] 可以表示时刻i末, 位于j状态的利润
f[n][1] 为所求
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        size_t n = prices.size();
        if (n <= 1)
            return 0;
        vector<vector<int>> f(n, vector<int>(3, 0));
        f[0][0] = -prices[0];
        f[0][1] = 0;
        f[0][2] = 0;

        for (int i = 1; i < n; i++) {
            f[i][0] = max(f[i-1][0], f[i-1][2]-prices[i]);  // 前一时刻持有, 或前一时刻不持有当前时刻买了(减了钱)
            f[i][1] = f[i-1][0]+prices[i];  // 当前时刻卖了(加了钱)
            f[i][2] = max(f[i-1][1], f[i-1][2]);    // 前一时刻卖了, 或者前一时刻不持有股票(当前时刻啥也没干)
        }

        return max(f[n - 1][1], f[n - 1][2]);
    }
};

int main() {
    vector<int> prices = {1,2};
    Solution solu;
    cout << solu.maxProfit(prices)<<endl;
    return 0;
}
