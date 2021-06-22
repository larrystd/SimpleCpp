/*
接雨水

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

最简单可以想到，对坐标为i的点，其能接雨水的大小为左右侧最小高度减去当前点的高度。且取值为正。

维护一个单调栈

*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    static int method_1(vector<int>& height) {
        if (height.size() < 3)
            return 0;
        int total_water = 0;
        for (int i = 1; i < height.size()-1; i++) {
            int max_left = 0;
            int max_right = 0;
            for (int j=i; j >= 0; j--) {
                max_left = max(max_left, height[j]);
            }
            for (int k = i; k <height.size(); k++) {
                max_right = max(max_right, height[k]);
            }
            total_water += (min(max_left, max_right) - height[i]);
        }
        return total_water;
    }

    static int method_2 (vector<int>& height) {
        int length = height.size();
        if (length < 3) 
            return 0;
        vector<int> left_height(length);
        vector<int> right_height(length);
        int total = 0;
        left_height[0] = height[0];
        right_height[length-1] = height[length-1];

        for (int i = 1; i < length; i++) {
            left_height[i] = max(height[i], left_height[i - 1]);
        }
        for (int j = length-2; j >= 0; j--) {
            right_height[j] = max(height[j], right_height[j+1]);
        }
        for (int i = 1; i < length - 1; i++) {
            total += min(left_height[i], right_height[i]) - height[i];
        }

        return total;
    }

    static int method_3 (vector<int>& height) {
        int ans = 0;
        stack<int> stk;
        int n = height.size();
        for (int i = 0; i < n; ++i) {
            // left, top, height[i]
            // 满足要求时三者形成
            while (!stk.empty() && height[i] > height[stk.top()]) {
                int top = stk.top();
                stk.pop();
                if (stk.empty()) {
                    break;
                }
                int left = stk.top();   // left存储的是下标
                int currWidth = i - left - 1;
                int currHeight = min(height[left], height[i]) - height[top];
                ans += currWidth * currHeight;
            }
            stk.push(i);
        }
        return ans;
    }


};

int main() {
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << Solution().method_1(height)<<endl;


    cout << Solution().method_2(height)<<endl;

    cout << Solution().method_3(height)<<endl;
    return 0;
}