/*
给你一个长度为 n 的整数数组，每次操作将会使 n - 1 个元素增加 1 。返回让数组所有元素相等的最小操作次数。

 

示例 1：

输入：nums = [1,2,3]
输出：3
解释：
只需要3次操作（注意每次操作会增加两个元素的值）：
[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool equalNums (vector<int>& nums) {
        int e = nums[0];
        for (auto& num : nums) {
            if (e != num)
                return false;
        }
        return true;
    }
    int minMoves(vector<int>& nums) {
        int step = 0;
        sort(nums.begin(), nums.end());
        int min = nums[0];
        for (auto& num : nums) {
            step += (num - min);
        }
        return step;
    }
};

int main() {
    Solution solu;
    vector<int> nums = {1,1000000000};
    cout << solu.minMoves(nums) <<endl;

    return 0;
}