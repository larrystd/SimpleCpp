#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> res;
    int countArrangement(int n) {
        vector<int> nums(n, 0);
        vector<int> track;
        for (int i = 0; i < n; i++) {
            nums[i] = i+1;
        }
        backtrack(track, nums);

        return res.size();
    }

    void backtrack(vector<int>& track, vector<int>& nums) {
        if (track.size() == nums.size()) {
            res.push_back(track);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (!count(track.begin(), track.end(), nums[i]) && (nums[i] % (track.size()+1) == 0 || (track.size()+1) % nums[i] == 0)) {
                track.push_back(nums[i]);
                backtrack(track, nums);
                track.pop_back();
            }
        
        }
    }

};

int main() {
    Solution s;
    cout << s.countArrangement(6) <<endl;

    return 0;
}