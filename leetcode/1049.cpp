#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        /// 从stones中选择，凑成质量不超过sum(stones)/2的最大值

        int n = stones.size();
        int sum = 0;
        for (auto& stone : stones) {
            sum+= stone;
        }
        int target = sum/2;

        vector<vector<int>> f(n+1, vector<int>(target));

        for (int i = 1; i <= stones.size(); i++) {
            for (int j = 1; j <= target; j++) {
                //cout << f[i][j] << " ";
                f[i][j] = f[i-1][j];
                if (j >= stones[i-1]) {
                    f[i][j] = max(f[i-1][j], f[i-1][j-stones[i-1]]+stones[i-1]);
                }
            }
        }

        return sum - 2*f[n][target];
    }
};

int main() {
    Solution solu;
    vector<int> stones = {31};
    cout << solu.lastStoneWeightII(stones)<<endl;
    return 0;
}