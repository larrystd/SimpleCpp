/*
等差数列划分

如果一个数列 至少有三个元素 ，并且任意两个相邻元素之差相同，则称该数列为等差数列。

例如，[1,3,5,7,9]、[7,7,7,7] 和 [3,-1,-5,-9] 都是等差数列。
给你一个整数数组 nums ，返回数组 nums 中所有为等差数组的 子数组 个数。

子数组 是数组中的一个连续序列。

要求是连续序列
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
// pair<int,int> 防止重复数字
    vector<vector<pair<int,int>>> res;
    unordered_map<int, int> index_map;

    int numberOfArithmeticSlices(vector<int>& nums) {
        vector<pair<int,int>> track;
        for (int i = 0; i < nums.size(); i++) {
            index_map[nums[i]+i*1000] = i;
        }
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

            if ( (size == 0) || (size == 1 && !count(track.begin(), track.end(), pair<int,int>(nums[i],i)) && (index_map[nums[i]+i*1000] - index_map[track[0].first+track[0].second*1000] == 1)) || (size >= 2 && !count(track.begin(), track.end(), pair<int,int>(nums[i],i)) && (track[1].first - track[0].first == nums[i] - track[size-1].first) && (index_map[nums[i]+i*1000] - index_map[track[size-1].first+track[size-1].second*1000] == 1) )) {
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
    vector<int> vect = {2,4,6,8,10};
    Solution s;
    cout << s.numberOfArithmeticSlices(vect) <<endl;
    return 0;

}