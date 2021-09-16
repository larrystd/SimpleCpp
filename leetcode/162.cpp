/*
峰值元素是指其值大于左右相邻值的元素。

给你一个输入数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞ 。

思路，二分法，对于中间值num[mid]，若num[mid-1] > num[mid] 则num[mid-1]那一侧一定有峰值。反之num[mid+1]
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findPeakValue(vector<int>& nums){
        if (nums.size() == 1)
            return 0;
        
        int left = 0, right = nums.size()-1;
        while  (left <= right) {
            int mid = (left + right)/2;
            if (mid == 0) {
                if (nums[mid] > nums[mid+1])
                    return mid;
                left = mid+1;
            }
            else if (mid == nums.size() - 1) {
                if (nums[mid] > nums[mid-1])
                    return mid;
                right = mid-1;
            }else {
                if (nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1])
                    return mid;
                if (nums[mid] <nums[mid+1])
                    left = mid+1;
                else if (nums[mid] < nums[mid-1])
                    right = mid-1;
            }   
        }

        return 0;
    }
};

int main(){
    Solution s;
    vector<int> vec = {1,2,1,3,5,6,4};
    cout << s.findPeakValue(vec)<<endl;
    return 0;

}