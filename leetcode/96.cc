// leetcode 96 不同的二叉搜索树
/*
给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的 二叉搜索树 有多少种？返回满足题意的二叉搜索树的种数。
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int result;
    int numTrees(int n) {
        result = 0;
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            nums[i] = i+1;
        }
        int num_select = 0;
        dfs(nums, 0, n-1, num_select);

        return result;
    }

    void dfs (vector<int>& nums, int left, int right, int& num_select) {
        if (left < 0 || right >= nums.size() || left > right)
            return;
        if (left == right && num_select == nums.size()-1) {
            result++;
            return;
        }
        if (left == right) {
            num_select++;
            return;
        }


        for (int i = left; i <= right; i++) {
            int temp = num_select;
            num_select ++;
            dfs(nums, left, i-1, num_select);
            dfs(nums, i+1,right, num_select);
            num_select = temp;
        }
    }
};

int main() {
    Solution solu;
    cout << solu.numTrees(4)<<endl;
}