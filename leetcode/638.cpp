#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int num;
    vector<int> price;
    int result;
    vector<vector<int>> special;
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        num = price.size();
        this->price = price;
        this->special = special;
        result = 0;
        for (int i = 0; i < price.size(); i++) {
            result += price[i] * needs[i];
        }
        dfs(needs, 0);
        return result;
    }

    void dfs(vector<int>& needs, int cost) {

        for (auto& sp : special) {
            // 是否可以购买sp
            bool isbuy = true;
            int i;
            for (i = 0; i < num; i++) {
                if (needs[i] < sp[i]) {
                    isbuy = false;
                    break;
                }
                needs[i] -= sp[i];
            }
            if (isbuy)
                dfs(needs, cost + sp[num]);
            for (int j = 0; j < i; j++) {   // 复原
                needs[j] += sp[j];
            }
        }
        /// 买不了大礼包了
        for (int i = 0; i < num; i++) {
            cost += needs[i]*price[i];
        }
        result = min(result, cost);
    }
};

int main() {
    Solution solu;
    vector<int> prices = {2,5};
    vector<vector<int>> special = {{3,0,5},{1,2,10}};
    vector<int> need = {3,2};
    cout << solu.shoppingOffers(prices, special, need);

    return 0;
}