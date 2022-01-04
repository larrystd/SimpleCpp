/*
给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static vector<vector<int>> subSet(vector<int>& nums) {
        vector<vector<int>> res;
        res.push_back(vector<int>());
        vector<int> tmp_set;
        dfs(res, tmp_set, nums, -1);
        return res;
    }

    static void dfs (vector<vector<int>>& res, vector<int>& tmp_set, vector<int>& nums, int start) {
        if (start>=0){
            tmp_set.push_back(nums[start]);
            res.push_back(tmp_set);
        }
        for (int i = start+1; i < nums.size(); i++) {
            dfs(res, tmp_set, nums, i);
            tmp_set.pop_back();
        }
    }
};

int main() {
    vector<int> height = {1,2,3};
    vector<vector<int>> res = Solution().subSet(height);
    for (int i = 0; i < res.size(); i++){
        for (int j = 0; j < res[i].size(); j++) {
            cout << res[i][j] << " ";
        }
        cout <<endl;
    }
}