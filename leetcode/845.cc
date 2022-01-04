/*
leetcode 845 数组最长山脉
把符合下列属性的数组 arr 称为 山脉数组 ：

arr.length >= 3
存在下标 i（0 < i < arr.length - 1），满足
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int size_ = arr.size();
        vector<int> dpleft(size_); 
        vector<int> dpright(size_);

        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] > arr[i-1])
                dpleft[i] = dpleft[i-1]+1;
            else  
                dpleft[i] = 0;
        }

        for (int i = arr.size()-2; i >=0; i--) {
            if (arr[i] > arr[i+1])
                dpright[i] = dpright[i+1]+1;
            else  
                dpright[i] = 0;
        }

        int result = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (dpleft[i] != 0 && dpright[i]!=0)
                result = max(result, dpleft[i]+dpright[i]+1);
        }
        return result;
    }
};

int main() {
    Solution solu;
    vector<int> nums = {2,2,2};
    cout << solu.longestMountain(nums)<<"\n";

    return 0;
}