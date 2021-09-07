/*
力扣周赛

给你一个 下标从 0 开始 的整数数组 nums ，返回满足下述条件的 不同 四元组 (a, b, c, d) 的 数目 ：

nums[a] + nums[b] + nums[c] == nums[d] ，且
a < b < c < d

4 <= nums.length <= 50
1 <= nums[i] <= 100
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int countQuadruplets(vector<int>& nums) {
        vector<int> track;
        int res = 0;
        backtrack(res, 0, nums, track);
        return res;
    }

    void backtrack(int& res, int k, vector<int>& nums, vector<int>& track) {
        if (track.size() == 4) {
            if (track[0] + track[1]+track[2] == track[3])
                res++;
            return;
        }
        for (int i = k; i < nums.size(); i++) {
            track.push_back(nums[i]);
            backtrack(res, i+1, nums,track);
            track.pop_back();
        }
    }
};

int main() {
    vector<int> nums = {3,3,6,4,5};
    Solution s;
    cout << s.countQuadruplets(nums)<<endl;
    return 0;
}
