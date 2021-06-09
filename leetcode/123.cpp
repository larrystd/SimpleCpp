#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
    int maxProfit (vector<int>& stocks){
        int max_profit = 0;

        dfs(stocks, 0, 0, 2, max_profit, 0);
        return max_profit;

    }

    void dfs (vector<int>& stocks, int block_start, int pos, int left_times, int& max_profit, int profit){
        if (left_times == 0){
            return;
        }
        profit += (stocks[pos] - stocks[block_start]);
        max_profit = max(max_profit, profit);

        for (int i = pos+1; i < stocks.size(); i++){
            if (stocks[i] > stocks[pos] && left_times > 0) // 买
                dfs(stocks, pos, i, left_times-1, max_profit, profit);
        }
    }
};