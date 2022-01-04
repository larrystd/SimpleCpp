/*
leetcode 5930
*/

#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    vector<vector<int>> tables;
    int maxDistance(vector<int>& colors) {
        int size = colors.size();
        tables.resize(size, vector<int>(size, -1));
        return dfs(0, size-1, colors);
    }

    int dfs(int left, int right, const vector<int>& nums) {
        if (left < 0 || right > nums.size()) 
            return 0;
        if (tables[left][right] != -1)
            return tables[left][right];
        if (nums[left] != nums[right])
            return right - left;
        tables[left][right] = max(dfs(left+1, right, nums), dfs(left, right-1, nums));
        return tables[left][right];
    }
};

int main() {
    vector<int> colors = {1,8,3,8,3};
    Solution solu;
    cout << solu.maxDistance(colors) <<endl;

    return 0;
}