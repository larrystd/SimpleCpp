// leetcode 646
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](auto& lhs, auto& rhs) {
            return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
        });
        int size = pairs.size();
        vector<int> dp(size, 1);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < i; j++) {
                if (pairs[j][1] < pairs[i][0])
                    dp[i] = max(dp[i], dp[j]+1);
            }
        }

        return *max_element(dp.begin(), dp.end());
    }
};

int main() {
    Solution solu;
    vector<vector<int>> nums = {{1,2}, {2,3}, {3,4}, {5,6}};
    cout << solu.findLongestChain(nums) << "\n";

    return 0;
}