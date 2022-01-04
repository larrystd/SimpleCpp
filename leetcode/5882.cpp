// 5882 网格游戏
#include  <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        int m  = 2;
        int n = grid[0].size();
        vector<vector<int>> f(m, vector<int>(n, 0));
        vector<vector<int>> dp(m, vector<int>(n, 0));

        f[0][0] = grid[0][0];
        f[1][0] = grid[1][0];

        for (int i = 1; i < n; i++) {
            f[0][i] = f[0][i-1]+grid[0][i];
            f[1][i] = max(f[1][i-1], f[0][i]) + grid[1][i];
        }
        printVect(f);
        /// 逆推
        //f[1][n-1] = 0;
        int i = 1;
        int j = n-1;

        while (i != 0 && j != 0) {
            grid[i][j] = 0;
            if (f[i-1][j] > f[i][j-1]) {
                i--;
            }else{
                j--;
            }
        }
        if (i == 0) {
            while (j) {
                grid[i][j--] = 0;
            }
        }
        if (j == 0) {
            while (i) {
                grid[i--][j] = 0;
            }
        }
        grid[i][j] = 0;
        printVect(grid);

        dp[0][0] = grid[0][0];
        dp[1][0] = grid[1][0];

        for (int i = 1; i < n; i++) {
            dp[0][i] = dp[0][i-1]+grid[0][i];
            dp[1][i] = max(dp[1][i-1], dp[0][i]) + grid[1][i];
        }
        printVect(dp);

        return dp[1][n-1];
    }


    long long gridGame_2(vector<vector<int>>& grid) {
        int m  = 2;
        int n = grid[0].size();
        vector<vector<long long>> f(m, vector<long long>(n, 0));
        vector<vector<long long>> dp(m, vector<long long>(n, 0));
        /*
        f[0][0] = grid[0][0];
        f[1][0] = grid[1][0];

        for (int i = 1; i < n; i++) {
            f[0][i] = f[0][i-1]+grid[0][i];
            f[1][i] = max(f[1][i-1], f[0][i]) + grid[1][i];
        }
        printVect(f);
        /// 逆推
        //f[1][n-1] = 0;
        int i = 1;
        int j = n-1;

        while (i != 0 && j != 0) {
            grid[i][j] = 0;
            if (f[i-1][j] > f[i][j-1]) {
                i--;
            }else{
                j--;
            }
        }
        if (i == 0) {
            while (j) {
                grid[i][j--] = 0;
            }
        }
        if (j == 0) {
            while (i) {
                grid[i--][j] = 0;
            }
        }
        grid[i][j] = 0;
        printVect(grid);
        */


        

        long long result = accumulate(grid[0].begin(), grid[0].end(), 0);
        result = accumulate(grid[1].begin(), grid[1].end(), result);
        
        for (int k = 0; k < n; k++) {
            dp.clear();
            dp.assign(m, vector<long long>(n, 0));
            if (k != 0) {
                //dp[0][0] = grid[0][0];
                dp[1][0] = grid[1][0];
            }

            for (int i = 1; i < n; i++) {
                if (i < k) {
                    dp[0][i] = dp[0][i-1];
                    dp[1][i] = max(dp[1][i-1], dp[0][i]) + grid[1][i];
                }else if (i > k) {
                    dp[0][i] = dp[0][i-1]+grid[0][i];
                    dp[1][i] = max(dp[1][i-1], dp[0][i]);
                }else {
                    dp[0][i] = dp[0][i-1];
                    dp[1][i] = max(dp[1][i-1], dp[0][i]);
                }
                
            }

            result = min<long long>(result, dp[1][n-1]);
        }


        //printVect(dp);

        return result;
    }

    void printVect(vector<vector<int>>& nums) {
        int m = nums.size();
        int n = nums[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << nums[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = {{20,3,20,17,2,12,15,17,4,15},{20,10,13,14,15,5,2,3,14,3}};
    
    //vector<vector<int>> grid = {{2,5,4},{1,5,1}};
    int res = s.gridGame_2(grid);
    cout << res<<endl;
    return 0;
}