#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        int left = 0;
        unordered_map<string,int> m;
        vector<string> res;
        int n = s.size();

        while (left <= n-10) {
            string sub_s = s.substr(left, 10);
            if (!m.count(sub_s))
                m[sub_s] = 1;
            else
                m[sub_s]++;
                
            left++;
        }
        for (unordered_map<string,int>::iterator iter = m.begin(); iter != m.end(); iter++) {
            if (iter->second>1)
                res.push_back(iter->first);
        }
        return res;
    }
};

int main() {
    string s =  "AAAA";
    Solution sol;
    vector<string> res = sol.findRepeatedDnaSequences(s);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] <<endl;
    }
    return 0;
}