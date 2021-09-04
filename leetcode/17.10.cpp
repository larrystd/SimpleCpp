#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        if (nums.size() <= 0)
            return -1;
        
        int count = 1;
        int major = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == major)
                count ++;
            else    
                count--;
            if (count < 0) {
                major = nums[i];
            }
        }

        int half = nums.size() >> 1;
        count = 0;
        for (int i : nums) {
            if (i == major)
                count++;
            if (count > half)
                return major;
        }
        return -1;
    }

};

int main() {
    vector<int> nums = {1,2,5,9,5,9,5,5,5};
    Solution s;
    cout << s.majorityElement(nums)<<endl;
    return 0;
}