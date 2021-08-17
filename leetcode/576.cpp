/*
576. 出界的路径数
给你一个大小为 m x n 的网格和一个球。球的起始坐标为 [startRow, startColumn] 。你可以将球移到在四个方向上相邻的单元格内（可以穿过网格边界到达网格之外）。你 最多 可以移动 maxMove 次球。

记忆化搜索或者动态规划
*/

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Solution {
public:
    // 移动方向
    const int MOD = pow(10,9) + 7;
    vector<vector<int>> dir = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    vector<vector<vector<int>>> cache;


    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        cache.clear();
        cache.resize(m, vector<vector<int>>(n, vector<int>(maxMove+1, -1)));
        // cache表示位置x,y 在k次Move下出界的路径

        return dfs(m, n, startRow, startColumn, maxMove);
    }

    int dfs (int m, int n, int x, int y, int k) {
        if (x >= m || x < 0 || y >= n || y < 0)
            return 1;
        if (k == 0)
            return 0;

        if (cache[x][y][k] != -1)
            return cache[x][y][k];
        int ans = 0;
        for (auto d : dir) {
            ans += dfs(m, n, x+d[0], y+ d[1], k-1);

            ans %= MOD;
        }
        cache[x][y][k] = ans;
        return ans;
    }

    int findPaths_dp(int m, int n, int maxMove, int startRow, int startColumn) {
        

        
    }

};

int main() {
    Solution s;
    cout << s.findPaths(2,2,2,0,0)<<endl;
    cout << s.findPaths(1,3,3,0,1)<<endl;

    return 0;
}