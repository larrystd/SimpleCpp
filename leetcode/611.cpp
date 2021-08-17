#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> res;

    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> track;
        backtrack(nums, track, 0);
        return res.size();
    }

    void backtrack(vector<int>& nums, vector<int>& track, int index) {
        if (track.size() == 3) {
            if (track[2] < (track[0] + track[1])) 
                res.push_back(track);
            return;
        }

        for (int i = index; i < nums.size(); i++) {
            track.push_back(nums[i]);
            backtrack(nums, track, i+1);
            track.pop_back();
        }
    }
};

int main() {
    vector<int> list = {2,2,3,4};
    Solution s;
    cout << s.triangleNumber(list) <<endl;
    return 0;
}