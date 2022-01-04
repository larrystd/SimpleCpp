/*
leetcode 718
最长重复子数组
给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。

输入：
A: [1,2,3,2,1]
B: [3,2,1,4,7]
输出：3
解释：
长度最长的公共子数组是 [3, 2, 1] 。
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();

        vector<vector<int>> dp(len1+1, vector<int>(len2+2));
        int result = 0;

        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (nums1[i-1] == nums2[j-1])
                    dp[i][j] = dp[i-1][j-1]+1;
                else 
                    dp[i][j] = 0;
                result = max(result, dp[i][j]);
            }
        }

        return result;
    }
};

int main() {
    vector<int> nums1 = {0,1,1,1,1};
    vector<int> nums2 = {1,0,1,0,1};

    Solution solu;
    cout << solu.findLength(nums1, nums2)<< "\n";

    return 0;
}