#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int n1 = s1.size();
        int n2 = s2.size();
        vector<vector<int>> dp (n1+1, vector<int>(n2+1, 0));

        for (int i = 1; i <= n1; i ++) {
            for (int j = 1; j <= n2; j++) {
                if (s1[i-1] == s2[j-1])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
        return dp[n1][n2];
    }

    // 状态压缩
    int longestCommonSubsequence_reduce(string s1, string s2) {
        int n1 = s1.size();
        int n2 = s2.size();
        vector<int> dp (n2+1, 0);

        for (int i = 1; i <= n1; i ++) {
            int pre = 0;
            // pre存储dp[i-1][j-1]
            for (int j = 1; j <= n2; j++) {
                int temp = dp[j];
                if (s1[i-1] == s2[j-1])
                    dp[j] = pre + 1;
                else
                    dp[j] = max(dp[j-1], dp[j]);
                
                pre = temp;
            }
        }
        return dp[n2];
    }
};

int main() {
    Solution s;

    string s1 = "zabcde";
    string s2 = "acez";

    cout << s.longestCommonSubsequence(s1, s2)<<endl;

    cout <<s.longestCommonSubsequence_reduce(s1, s2)<<endl;

    return 0;
}