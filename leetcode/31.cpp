/*
实现获取 下一个排列 的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须 原地 修改，只允许使用额外常数空间。

示例 1：

输入：nums = [1,2,3]
输出：[1,3,2]

理论上交换数字是最简单的办法，
123 132 213 231 312 321 123

从后开始算,拿递增的大于前面的最小数代替前方的数，前方数放到后面最大的
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int> &nums){
        if (nums.size() == 1)
            return;
        int i = nums.size() - 1;
        while (nums[i] < nums[i-1])
            i--;
        int temp = nums[i-1];
        int front_index = i-1;
        
        while (i < nums.size() && nums[i] > temp)
            i++;
        nums[front_index] = nums[i-1];
        while (i < nums.size() && nums[i] < temp){
            nums[i-1] = nums[i];
            i++;
        }
        nums[i-1] = temp;
    }
};

int main() {
    Solution s;
    vector<int> vec = {1,3,2};
    s.nextPermutation(vec);

    for (int i = 0; i < vec.size(); i++){
        cout<<vec[i] <<" ";
    }
    return 0;
}

