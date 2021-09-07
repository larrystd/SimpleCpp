/*
编写一种方法，对字符串数组进行排序，将所有变位词组合在一起。变位词是指字母相同，但排列不同的字符串。

注意：本题相对原题稍作修改
*/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        vector<vector<string>> res;
        for(string s : strs) {
            string temp(s);
            sort(temp.begin(), temp.end());
            if (!m.count(temp)){
                m[temp] = vector<string>{s};
            }else{
                m[temp].push_back(s);
            }
        }
        for(unordered_map<string, vector<string>>::iterator iter = m.begin(); iter != m.end(); iter++) {
            res.push_back(iter->second);
        }
        return res;
        
    }
};