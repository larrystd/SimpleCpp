// 最长递增子序列的个数

/*
给定一个未排序的整数数组，找到最长递增子序列的个数。

示例 1:

输入: [1,3,5,4,7]
输出: 2
解释: 有两个最长递增子序列，分别是 [1, 3, 4, 7] 和[1, 3, 5, 7]。

表示以n为结尾的
f[n] 表示当前最长子序列长度
g[n] 表示当前个数
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(n, 1);    // 长度
        vector<int> g(n, 1);    // 个数

        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                           /// 以i结尾的最长子序列长度, 有两种选择
                    if (f[j]+1 > f[i]){ // 有要选的元素, j作为i为尾最长序列前一个元素
                        f[i] = f[j] + 1;  
                        g[i] = g[j];
                    }    
                    else if (f[j]+1 == f[i]) {   // 这个j也可以选
                        g[i] += g[j];
                    }
                }  
            }
        }

        int result = 0;
        int max_seq = 0;
        for (int i = 0; i < n; i++) {
            if (f[i] > max_seq) {
                max_seq = f[i];
                result = g[i];
            }else if (f[i] == max_seq) {
                result += g[i];
            }
        }

        return result;
    }
};

int main() {
    vector<int> nums = {2,2,2,2,2};

    Solution solu;
    cout << solu.findNumberOfLIS(nums) <<endl;

    return 0;
}
