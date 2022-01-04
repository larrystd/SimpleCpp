#include <vector>
#include <algorithm>
#include <array>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<array<int, 2>> heights(n);   // 每一行, 每一列的最大值
        for (int i = 0; i < n; i++) {
            heights[i][0] = *max_element(grid[i].begin(), grid[i].end());

            heights[i][1] = -1;
            for (int j = 0; j < n; j++) {
                heights[i][1] = max(heights[i][1], grid[j][i]);
            }
        }

        for (auto arr : heights) {
            cout << arr[0]<<" "<<arr[1]<<"\n";
        }

        int result = 0;
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j++) {
                int diffheight = min(heights[i][0], heights[j][1])-grid[i][j];
                diffheight>0 ? result+=diffheight : 0;
            }
        }

        return result;
    }
};

int main() {
    Solution solu;
    vector<vector<int>> nums = {{3,0,8,4},{2,4,5,7},{9,2,6,3},{0,3,1,0}};

    cout << solu.maxIncreaseKeepingSkyline(nums) << "\n";

    return 0;
}