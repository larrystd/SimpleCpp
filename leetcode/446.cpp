/*
446. 等差数列划分 II - 子序列
给你一个整数数组 nums ，返回 nums 中所有 等差子序列 的数目。

如果一个序列中 至少有三个元素 ，并且任意两个相邻元素之差相同，则称该序列为等差序列。

例如，[1, 3, 5, 7, 9]、[7, 7, 7, 7] 和 [3, -1, -5, -9] 都是等差序列。
再例如，[1, 1, 2, 5, 7] 不是等差序列。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<pair<int,int>>> res;

    int numberOfArithmeticSlices(vector<int>& nums) {
        vector<pair<int,int>> track;
        backtrack(nums, track,0);

        return res.size();
    }

    void backtrack(vector<int>& nums, vector<pair<int,int>>& track, int index) {
        if (track.size() >= 3) {
            res.push_back(track);
            //return;
        }
        for (int i = index; i < nums.size(); i++) {
            int size = track.size();
            if (nums[i] < 0)
                continue;
            if ( (size == 0) || (size == 1 && !count(track.begin(), track.end(), pair<int,int>(nums[i],i))) || (size >= 2 && !count(track.begin(), track.end(), pair<int,int>(nums[i],i)) && (track[1].first - track[0].first == nums[i] - track[size-1].first) )) {
                track.push_back(pair<int,int>(nums[i],i));
                backtrack(nums, track,i+1);
                track.pop_back();
            } 
            /*
            if (size >= 2 && !count(track.begin(), track.end(), nums[i]) && (track[1] - track[0] == nums[i] - track[size-1])) {
                track.push_back(nums[i]);
                backtrack(nums, track);
                track.pop_back();
            }
            */
        }
    }
};


int main() {
    vector<int> vect = {0,2000000000,-294967296};
    Solution s;
    cout << s.numberOfArithmeticSlices(vect) <<endl;
    return 0;

}