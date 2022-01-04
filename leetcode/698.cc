/*
698. 划分为k个相等的子集
输入： nums = [4, 3, 2, 3, 5, 2, 1], k = 4
输出： True
说明： 有可能将其分成 4 个子集（5），（1,4），（2,3），（2,3）等于总和。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum_ = accumulate(nums.begin(), nums.end(), 0);
        if (sum_ % k != 0)
            return false;
        int target = sum_ / k;
        sort(nums.begin(), nums.end(), greater<int>());
        vector<int> visited(nums.size());
        return dfs(nums, visited, target, 0, 0, k);
    }

    bool dfs(vector<int>& nums, vector<int>& visited, int target, int cursum, int curpart, int k) {
        if (cursum > target)
            return false;
        if (cursum == target) {
            curpart ++;
            cursum  = 0;
        }
        if (curpart == k)
            return true;
        for (int i = 0; i < nums.size(); i++) {
            if (!visited[i]) {
                visited[i] = 1;
                if (dfs(nums, visited, target, cursum+nums[i], curpart, k))
                    return true;
                visited[i] = 0;
            }
        }

        return false;
    }

};

class Solutionv2 {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum_ = accumulate(nums.begin(), nums.end(), 0);
        if (sum_ % k != 0)
            return false;
        int target = sum_ / k;
        int size_ = nums.size();
        //sort(nums.begin(), nums.end(), greater<int>());
        vector<int> visited(size_);

        for(int i=0; i<size_; i++){
            if(visited[i])  continue;
            if(!dfs(i+1,target-nums[i],visited,nums))
                return false;
        }
        return true;
    }

     bool dfs(int beg, int target, vector<int>& visited, vector<int>& nums){
        if(target==0)return true;
        if(beg==nums.size())return false;

        for(int i=beg;i<nums.size();i++){
            if(visited[i])  continue;
            if(nums[i]>target)  continue;
            visited[i]=1;
            if(dfs(i+1,target-nums[i],visited,nums))
                return true;
            visited[i]=0;
        }
        return false;
    }
};

int main() {
    Solutionv2 solu;
    vector<int> nums = {2,1,1,3,2,3};
    int k = 3;

    cout << solu.canPartitionKSubsets(nums, k) << "\n";

    return 0;
}