/*
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

输入：[7,1,5,3,6,4]
输出：5
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int> stocks){
        int min_value = stocks[0];
        int max_profit = 0;

        for (int i = 1; i < stocks.size(); i++){
            max_profit = max(max_profit, stocks[i] - min_value);
            min_value = min(min_value, stocks[i]);
        }

        return max_profit;
    }
};

int main(){
    vector<int> stocks = {7,6,4,3,1};
    Solution s;
    cout << s.maxProfit(stocks) <<endl;
    return 0;
}