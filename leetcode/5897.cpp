/*
5897. 将数组分成两个数组并最小化数组和的差
给你一个长度为 2 * n 的整数数组。你需要将 nums 分成 两个 长度为 n 的数组，分别求出两个数组的和，并 最小化 两个数组和之 差的绝对值 。nums 中每个元素都需要放入两个数组之一。

请你返回 最小 的数组和之差。

简单的两种决策,dfs

输入：nums = [3,9,7,3]
输出：2
解释：最优分组方案是分成 [3,9] 和 [7,3] 。
数组和之差的绝对值为 abs((3 + 9) - (7 + 3)) = 2 。

*/
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
    int sum_nums;
    int len;
    int minimumDifference(vector<int>& nums) {
        sum_nums = accumulate(nums.begin(), nums.end(), 0);
        int result = 0;
        for (auto& num: nums) {
            result+= abs(num);
        }
        len = nums.size();

        trackback(0, nums, 0, result, 0);
        
        return result;

    }

    void trackback(int num_choose, vector<int>& nums, int sum_choose, int& result, int index) {
        if (index == len)
            return;
        if (num_choose > len/2)
            return;
        if (num_choose == len/2 && result > abs(2*sum_choose - sum_nums))
            result = abs(2*sum_choose - sum_nums);
        // 选
        trackback(num_choose+1, nums, sum_choose+nums[index], result, index+1);
        trackback(num_choose, nums, sum_choose, result, index+1);
    }
};

int main() {
    vector<int> nums = {7772197,4460211,-7641449,-8856364,546755,-3673029,527497,-9392076,3130315,-5309187,-4781283,5919119,3093450,1132720,6380128,-3954678,-1651499,-7944388,-3056827,1610628,7711173,6595873,302974,7656726,-2572679,0,2121026,-5743797,-8897395,-9699694};
    Solution solu;
    cout << solu.minimumDifference(nums)<<endl;
    return 0;
}
