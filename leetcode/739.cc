// leetcode 739
// 请根据每日 气温 列表 temperatures ，请计算在每一天需要等几天才会有更高的温度。如果气温在这之后都不会升高，请在该位置用 0 来代替。
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        unordered_map<int, int> tables; // 元素对应下标
        stack<int> temperstack;
        vector<int> nextbig_range;
        int size = temperatures.size();
        temperstack.push(temperatures[size-1]);
        nextbig_range.push_back(0);
        tables[temperatures[size-1]] = size-1;

        for (int i = size-2; i >= 0; i--) {
            tables[temperatures[i]] = i;
            while (!temperstack.empty()) {
                int temp = temperstack.top();
                if (temp > temperatures[i]) {
                    nextbig_range.push_back(tables[temp] - i);
                    temperstack.push(temperatures[i]);
                    break;
                }
                temperstack.pop();
            }
            if (temperstack.empty()) {
                nextbig_range.push_back(0);
                temperstack.push(temperatures[i]);
            }
        }
        reverse(nextbig_range.begin(), nextbig_range.end());
        return nextbig_range;
    }
};

int main() {
    Solution solu;
    vector<int> nums = {30,40,50,60};
    vector<int> results = solu.dailyTemperatures(nums);

    for (auto e : results) {
        cout << e << " ";
    }

    return 0;
}