#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));

        bool isstop = false;
        for (int i = 0; i < m; i++) {
            if (!isstop)
                dp[i][0] = 1;
            else 
                dp[i][0] = 0;
            if (obstacleGrid[i][0] == 1) {
                dp[i][0] = 0;
                isstop = true;
            }
        }
        isstop = false;
        for (int i = 0; i < n; i++) {
            if (!isstop)
                dp[0][i] = 1;
            else 
                dp[0][i] = 0;
            if (obstacleGrid[0][i] == 1) {
                dp[0][i] = 0;
                isstop = true;
            }
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                }
                else {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
            }
        }

        return dp[m-1][n-1];
    }
};

int main() {
    vector<vector<int>> grid = {{1}};

    Solution solu;
    cout << solu.uniquePathsWithObstacles(grid) << "\n";

    return 0;
}