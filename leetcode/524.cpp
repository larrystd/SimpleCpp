// 524. 通过删除字母匹配到字典里最长单词

/*
给你一个字符串 s 和一个字符串数组 dictionary 作为字典，找出并返回字典中最长的字符串，该字符串可以通过删除 s 中的某些字符得到。

如果答案不止一个，返回长度最长且字典序最小的字符串。如果答案不存在，则返回空字符串。

输入：s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
输出："apple"
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <deque>

/// set内部可以自定义规则排序
using namespace std;

class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {

        int max_len = 0;
        set<string> result;
        for (string& str : dictionary) {

            int i=0 ,j =0;
            while (i < s.size() && j < str.size()) {
                if (s[i] == str[j]){
                    i++;
                    j++;
                }else {
                    i++;
                }
            }
            

            if (j == str.size()) {
                if (max_len < str.size()) {
                    result.clear();
                    result.insert(str);
                    max_len = str.size();
                }else if (max_len == str.size()) {
                    result.insert(str);
                }
            }
        }

        return result.size()==0 ? "" : *result.begin();
    }
};

int main() {
    vector<string> dict = {"zxc","vbn"};
    string s = "apple";
    Solution obj;
    cout << obj.findLongestWord(s, dict) << endl;
    return 0;
}