/*
找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字。

例如输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<vector<int>> res;

    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int>track;
        int maxnum = 9;
        vector<int> nums(maxnum, 0);
        for (int i = 0; i < maxnum; i++) {
            nums[i] = i+1;
        }

        backtrack(nums, track, n, k, 0);

        return res;


    }

    void backtrack(vector<int>& nums, vector<int>& track, int n, int k, int index) {
        if (k == 0 && accumulate(track.begin(), track.end(), 0) == n) {
            res.push_back(track);
            return;
        }
        if (accumulate(track.begin(), track.end(), 0) > n) 
            return;
        
        for (int i = index; i < nums.size(); i++) {
            if (!count(track.begin(), track.end(), nums[i])){
                track.push_back(nums[i]);
                backtrack(nums, track, n, k-1, i+1);
                track.pop_back();
            }
        }
    }
};

int main() {
    Solution s;

    vector<vector<int>> res = s.combinationSum3(3,9);

    for (int i = 0; i < res.size(); i++) {
        for (int j =  0; j < res[i].size(); j++) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
}