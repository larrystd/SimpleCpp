/*
leetcode 560 和为k的子数组
给你一个整数数组 nums 和一个整数 k ，请你统计并返回该数组中和为 k 的连续子数组的个数。
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int win_sum = 0;
        int left = 0, right = 0;
        int result = 0;
        for (right = 0; right < nums.size(); right++) {
            win_sum += nums[right];
            if (win_sum == k)
                result++;
            while (left <= right && win_sum >= k) {
                win_sum -= nums[left];
                left++;
                if (win_sum == k)
                    result++;
            }

        }
        return result;
    }
};