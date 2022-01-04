#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int result;
    int curval;
    int countMaxOrSubsets(vector<int>& nums) {
        result = 0;
        curval = 0;
        backtrack(nums, 0, 0);
        return result;  
    }

    void backtrack(vector<int>& nums, int cur, int index) {
        if (index == nums.size()) {
            //int cur = 0;
            //for (auto& num : track) {
            //    cur |= num;
            //}
            //result = max(result, cur);
            if (curval < cur) {
                result = 1;
                curval = cur;
            }else if(curval == cur) {
                result++;
            }
            return;
        }

        backtrack(nums, cur, index+1);

        //track.push_back(nums[i]);
        cur |= nums[index];
        backtrack(nums, cur, index+1);
        //track.pop_back();
    }
};

int main() {
    vector<int> nums = {3,1};
    Solution solu;
    cout << solu.countMaxOrSubsets(nums) <<endl;


    return 0;
}