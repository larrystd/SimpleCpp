/* leetcode 451 根据字符出现频率排序

给定一个字符串，请将字符串里的字符按照出现的频率降序排列。

输入:
"Aabb"

输出:
"bbAa"

解释:
此外，"bbaA"也是一个有效的答案，但"Aabb"是不正确的。
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> m;
        vector<pair<char,int>> temp;
        string res = "";

        for (char c : s) {
            if (!m.count(c)) 
                m[c] = 1;
            else
                m[c] ++;
        }
        for (auto p : m) {
            temp.push_back(p);
        }

        sort(temp.begin(), temp.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        for (auto p : temp) {
            for (int i = 0; i < p.second; i++) {
                res.push_back(p.first);
            }
        }

        return res;

    }
};

int main() {
    Solution s;
    cout << s.frequencySort("")<<endl;
    return 0;
}
