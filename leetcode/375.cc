/*
我们正在玩一个猜数游戏，游戏规则如下：

我从 1 到 n 之间选择一个数字。
你来猜我选了哪个数字。
如果你猜到正确的数字，就会 赢得游戏 。
如果你猜错了，那么我会告诉你，我选的数字比你的 更大或者更小 ，并且你需要继续猜数。
每当你猜了数字 x 并且猜错了的时候，你需要支付金额为 x 的现金。如果你花光了钱，就会 输掉游戏 。
给你一个特定的数字 n ，返回能够 确保你获胜 的最小现金数，不管我选择那个数字 

每次选择一个数字, 下次从该数组的两侧区间进行决策
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> cache;

    int getMoneyAmount(int n) {
        cache.resize(n+1, vector<int>(n+1));
        return dfs(1, n);
    }

    int dfs(int l, int r) {
        if (l >= r)
            return 0;
        if (cache[l][r] != 0)
            return cache[l][r]; // 在[l,r]的猜正确数字的最小花费
        int ans = 0x3f3f3f3f;
        for (int i = l; i <= r; i++) {
            int cur = max(dfs(l,i-1), dfs(i+1, r)) + i; // 选了i, 保证可以猜到数字的花费。两侧的较大值+i
            ans = min(cur, ans);    // 保证可以猜到数字的最小花费
        }
        cache[l][j] = ans;

        return ans;
    }
};

int main() {
    Solution solu;
    cout << solu.getMoneyAmount(10) <<endl;

    return 0;
}