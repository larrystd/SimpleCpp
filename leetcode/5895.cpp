#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int m = grid.size();
        int n = grid[0].size();
        int len = m*n;
        if (len == 1)
            return 0;

        vector<int> nums;
        for (auto& g: grid) {
            for (int num: g) {
                nums.push_back(num);
            }
        }
        sort(nums.begin(), nums.end());
        /// 中间数
        vector<int> num_steps = {0,0};
        vector<int> backups = {nums[len/2], nums[len/2-1]};
        for (int i = 0; i < backups.size(); i++) {
            for (int num : nums) {
                if (abs(num-backups[i]) % x != 0)
                    return -1;
                num_steps[i] += abs(num-backups[i])/x;
            }
        }

        return min(num_steps[0], num_steps[1]);
    }
};

int main() {
    vector<vector<int>> grid = {{1,5},{2,3}};
    Solution solu;
    cout << solu.minOperations(grid, 1)<<endl;
    return 0;
}