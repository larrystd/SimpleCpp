class Solution {
public:
    int findLHS(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int left = 0;
        int right = 0;
        int res = 0;
        for (right = 0; right < nums.size(); right++) {
            if (nums[right] - nums[left] == 1) { // 如果满足相差为1, 更新res
                res = max(res, right - left + 1);
            }
            while (nums[right] - nums[left] > 1) {  // 如果相差>1, 则需要更新left 
                left++;
            }
        }
        return res;
    }
};