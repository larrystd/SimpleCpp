/*
368. 最大整除子集
给你一个由 无重复 正整数组成的集合 nums ，请你找出并返回其中最大的整除子集 answer ，子集中每一元素对 (answer[i], answer[j]) 都应当满足：
answer[i] % answer[j] == 0 ，或
answer[j] % answer[i] == 0
如果存在多个有效解子集，返回其中任何一个均可。

示例 1：

输入：nums = [1,2,3]
输出：[1,2]
解释：[1,3] 也会被视为正确答案。

方法，动态规划, f[i]为以i为结尾的最大整除序列的长度
*/
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(n, 1);

        sort(nums.begin(), nums.end());
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j ++) {
                if (nums[i] % nums[j] == 0) {
                    f[i] = max(f[i], f[j]+1);
                }
            }
        }

        int max_f = 0;
        int max_num;
        int max_id;
        for (int i = 0; i < n; i++) {
            if (f[i] > max_f) {
                max_f = f[i];
                max_num = nums[i];
                max_id = i;
            }
        }
        vector<int> result;
        result.push_back(max_num);
        int next_f = max_f;

        for (int i = max_id-1; i >= 0; i--) {
            if (max_num % nums[i] == 0 && f[i]==next_f-1) {
                result.push_back(nums[i]);
                max_num = nums[i];
                next_f = f[i];
            }
        }
        assert(next_f == 1);
        reverse(result.begin(), result.end());
        return result;

    }
};

int main() {
    Solution solu;
    vector<int> nums = {4,8,10,240};

    auto result = solu.largestDivisibleSubset(nums);

    for (auto& num : result) {
        cout << num<<endl;
    }
    

    return 0;
}
