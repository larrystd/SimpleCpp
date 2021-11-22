#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    int max_num;
    int goal;
    int result;
    set<int> set_num;
    int minimumOperations(vector<int>& nums, int start, int goal) {
        max_num = *max_element(nums.begin(), nums.end());
        this->goal = goal;
        result = 10000000;
        dfs(nums, start, 0, '+', 0);

        return result;
    }


    void dfs(vector<int>& nums, int cur, int step, char sym, int num) {
        if (set_num.count (cur))
            return;
        set_num.insert(cur);
        if (cur > 1000 || cur < 0) {
            int mod = (goal-cur) % num;
            if (mod == 0) {
                if (goal > cur && sym == '+') {
                    result = min(step+(goal-cur) % num, result);
                }
                if (goal < cur && sym == '-') {
                    result = min(step+(cur-goal) % num, result);
                }
            }
            return;
        }
        if (cur == goal) {
            if (result == 10000000)
                result = step;
            result = min(step, result);
            //return;
        }
        for (auto& num : nums) {
            dfs(nums, cur + num, step+1, '+', num);
            //cout << cur << endl;
            dfs(nums, cur - num, step+1, '-', num);

            dfs(nums, cur ^ num, step+1, '^', num);
        }
    }
};

int main() {
    Solution solu;
    vector<int> nums = {2,4,12};
    int start = 2;
    int goal = 12;

    cout << solu.minimumOperations(nums, start, goal);

    return 0;
}