/// leetcode 714  买卖股票的最佳时机含手续费

/*
给定一个整数数组 prices，其中第 i 个元素代表了第 i 天的股票价格 ；整数 fee 代表了交易股票的手续费用。
你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
返回获得利润的最大值。

注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

输入：prices = [1, 3, 2, 8, 4, 9], fee = 2
输出：8
解释：能够达到的最大利润:  
在此处买入 prices[0] = 1
在此处卖出 prices[3] = 8
在此处买入 prices[4] = 4
在此处卖出 prices[5] = 9
总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8

f[i][0] 表示持有股票
f[i][1] 表示不持有股票
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        size_t n = prices.size();
        if (n <= 1)
            return 0;
        vector<vector<int>> f(n, vector<int>(2,0));
        f[0][0] = -prices[0]-fee;

        for (int i = 1; i < n; i++) {
            f[i][0] = max(f[i-1][0], f[i-1][1]-prices[i]-fee);
            f[i][1] = max(f[i-1][1], f[i-1][0]+prices[i]);
        }

        return f[n-1][1];
        
    }
};

int main() {
    vector<int> prices = {1, 3, 2, 8, 4, 9};
    int fee = 13;

    Solution solu;
    cout << solu.maxProfit(prices, fee)<<endl;
    return 0;
}

