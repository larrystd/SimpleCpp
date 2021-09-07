// 525. 连续数组

// 给定一个二进制数组 nums , 找到含有相同数量的 0 和 1 的最长连续子数组，并返回该子数组的长度。

// 本题类似525

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> use_map;
        int n = nums.size();
        vector<int> prefix_nums(n+1, -1);
        for (int i = 1; i <= n; i++) {
            if (nums[i-1] == 0)
                prefix_nums[i] = -1 + prefix_nums[i-1];
            else
                prefix_nums[i] = 1 + prefix_nums[i-1];
        }

        int max_len = 0;
        for (int i = 0; i <= n; i++) {
            if (!use_map.count(prefix_nums[i])) {
                use_map[prefix_nums[i]] = i;
            }
            else {
                max_len = max(max_len, i - use_map[prefix_nums[i]]);
            }
        }

        return max_len;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1,0,1,0,1};
    cout << s.findMaxLength(nums)<<endl;
    return 0;
}