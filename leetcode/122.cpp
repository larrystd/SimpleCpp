/*
给定一个数组 prices ，其中 prices[i] 是一支给定股票第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

输入: prices = [7,1,5,3,6,4]
输出: 7
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int> stocks){
        int max_profit = 0;

        for (int i = 1; i < stocks.size(); i++){
            if (stocks[i] - stocks[i-1] > 0){
                max_profit += stocks[i] - stocks[i-1];
            }
        }

        return max_profit;
    }
};

int main(){
    vector<int> stocks = {7};
    Solution s;
    cout << s.maxProfit(stocks) <<endl;
    return 0;
}