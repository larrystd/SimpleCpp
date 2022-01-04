/*
打家劫舍II

你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。

给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，今晚能够偷窃到的最高金额。

这道题可以这样分析
只有一间房屋，只能偷窃这一间
有两间房屋，偷窃这两间钱多的

三间房屋以上，只需要记住，首尾不能同时偷。
也就是在[0~length-2]和[1~length-1]两个数组中选结果大的那个即可。
dp[i] 表示偷盗[0~i]房屋时偷钱的最大值
状态转移方程未dp[i] = max(dp[i-1] + dp[i-2]+a[i])
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int stealMoney(vector<int> money) {
        if (money.size() == 1)
            return money[0];
        if (money.size() == 2)
            return max(money[0], money[1]);
        if (money.size() == 3) {
            return max(max(money[0], money[1]), money[2]);
        }
        int length = money.size();
        vector<int> dp(money.size());
        dp[0] = money[0];
        dp[1] = max(money[0], money[1]);

        for (int i = 2; i < length-1; i++) {
            dp[i] = max(dp[i-1], dp[i-2] + money[i]);
        }
        
        vector<int> dp_2(money.size());
        dp_2[1] = money[1];
        dp_2[2] = max(money[1],money[2]);
        for (int i = 3; i < length; i++) {
            dp_2[i] = max(dp_2[i-1], dp_2[i-2] + money[i]);
        }

        return max(dp[length-2], dp_2[length-1]);
    }
};

int main() {
    vector<int> money = {2,3,2};
    Solution s;
    cout << s.stealMoney(money) <<endl;
    return 0;
}
