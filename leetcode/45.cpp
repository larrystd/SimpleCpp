/*
给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。

假设你总是可以到达数组的最后一个位置。

输入: [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static int minJump (vector<int>& arr) {
        if (arr.size() == 1)
            return 0;
        vector<int> num_step(arr.size());
        int range = 0;

        for (int i = 0; i < arr.size()-1; i++) {
            for (int j = range+1; j <= i+arr[i]; j++) {
                if (j == arr.size()-1)
                    return  num_step[i]+1;
                num_step[j] = num_step[i]+1;
                range = i+arr[i];
            }
        }
        return -1;
    }
};

int main() {
    vector<int> arr = {1,2,1,1,1};
    cout << Solution().minJump(arr)<<endl;

    return 0;
}