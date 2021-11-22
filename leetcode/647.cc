// leetcode 647 回文子串

/*
回文字符串 是正着读和倒过来读一样的字符串。
子字符串 是字符串中的由连续字符组成的一个序列。
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int countSubstrings(string s) {
        int result = 0;
        int size = s.size();
        tables.resize(size, vector<int>(size, -1));
        for (int i = 0; i < size; i ++) {
            result += dfs(i, i, s);
        }
        for (int i = 0; i < size-1; i ++) {
            if (s[i] == s[i+1])
                result += dfs(i, i+1, s);
        }
        return result;
    }

    int dfs (int left, int right, const string& nums) {
        if (left < 0 || right >= nums.size())
            return 0;
        if (left > right)
            return 0;
        if (nums[left] != nums[right])
            return 0;
        if (tables[left][right] != -1)  // 已经计算过了
            return 0;
        int ans = 0;
        ans = dfs(left-1,right+1, nums) + 1;
        tables[left][right] = ans;
        return ans;
    }
private:
    vector<vector<int>> tables;
};

int main() {
    string s("dnncbwoneinoplypwgbwktmvkoimcooyiwirgbxlcttgteqthcvyoueyftiwgwwxvxvg");
    Solution solu;
    cout << solu.countSubstrings(s);
    return 0;
}