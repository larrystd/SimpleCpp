#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:

    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort (envelopes.begin(), envelopes.end(), [](const auto& a, const auto& b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
        });

        /// 最长上升子序列
        int n = envelopes.size();
        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++){
                if (envelopes[i][1] > envelopes[i-1][1])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        int max_increase_length = 0;
        for (int i = 0; i < n; i++)
            if (dp[i] > max_increase_length)
                max_increase_length = dp[i];
        return max_increase_length;
    }
};

int main(){
    vector<vector<int>> vect = {{5,4},{6,4},{6,7},{2,3}};

    Solution s;
    cout << s.maxEnvelopes(vect)<<endl;

    return 0;
}