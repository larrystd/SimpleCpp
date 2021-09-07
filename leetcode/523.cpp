// 523 连续的子数组和

/* 给你一个整数数组 nums 和一个整数 k ，编写一个函数来判断该数组是否含有同时满足下述条件的连续子数组：

子数组大小 至少为 2 ，且
子数组元素总和为 k 的倍数。
如果存在，返回 true ；否则，返回 false 。

如果存在一个整数 n ，令整数 x 符合 x = n * k ，则称 x 是 k 的一个倍数。0 始终视为 k 的一个倍数。
*/

#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool checkSubarraySum_2(vector<int>& nums, int k) {
        int n = nums.size();
        map<int, int> use_map;
        vector<int> prefix_nums(n+1,0);

        for (int i = 1; i <= nums.size(); i++) {
            prefix_nums[i] = prefix_nums[i-1] + nums[i-1];
        }

        for (int j = 0; j < prefix_nums.size(); j++) {
            if (! use_map.count(prefix_nums[j] % k)) {
                use_map[prefix_nums[j] % k] = j;
            }else {
                if (j - use_map[prefix_nums[j] % k] >= 2)
                    return true;
            }
        }

        return false;

    }


    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        int prefix_sum = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            prefix_sum += nums[i];
            m[i] = prefix_sum;
        }

        for (auto&& iter = m.begin(); iter != m.end(); iter++) {
            int temp = iter->second;
            if (temp % k == 0)
                return true;
            // 子数组长度至少为2
            for (int i = 0; i < iter->first-1; i++) {
                temp -= nums[i];
                if (temp % k == 0)
                    return true;
            }
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1,2,12};
    cout << s.checkSubarraySum_2(nums, 6)<<endl;
    return 0;
}