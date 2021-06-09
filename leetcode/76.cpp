/*
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。

输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"

1 <= s.length, t.length <= 1e5
s 和 t 由英文字母组成
*/

/*
用滑动窗口的思想解决这个问题。在滑动窗口类型的问题中都会有两个指针，一个用于「延伸」现有窗口的 rr 指针，和一个用于「收缩」窗口的 ll 指针。
在任意时刻，只有一个指针运动，而另一个保持静止。我们在 ss 上滑动窗口，通过移动 rr 指针不断扩张窗口。
当窗口包含 tt 全部所需的字符后，如果能收缩，我们就收缩窗口直到得到最小窗口。
具体的，rr指针右移直到包含所有字符，ll指针左移直到不包含字符。记录窗口。
rr继续右移,ll左移，在记录窗口。直到结束。

如何判断当前的窗口包含所有 tt 所需的字符呢？我们可以用一个哈希表表示 tt 中所有的字符以及它们的个数，用一个哈希表动态维护窗口中所有的字符以及它们的个数，
如果这个动态表中包含 tt 的哈希表中的所有字符，并且对应的个数都不小于 tt 的哈希表中各个字符的个数，那么当前的窗口是「可行」的。
注意记录各个字符的个数
*/

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Solution{
public:
/*
check过程用两个map
*/
    bool isContain(const string& s, const map<char,int>& mp){
        map<char,int> mp_copy(mp);
        for (int i = 0; i < s.size(); i++){
            if (mp_copy.count(s[i])){
                mp_copy[s[i]] --;
            }
            if (mp_copy[s[i]] == 0)
                mp_copy.erase(s[i]);  
            if (mp_copy.empty())
                return true;
        }
        return false;
    }

    string findString(string s, string t){
        int rr = 0;
        int ll = 0;

        int windowSize = s.size();
        int res_left = 0;

        map<char,int> mp;
        for (int i = 0; i < t.size(); i++){
            if (mp.count(t[i])){
                mp[t[i]]++;
            }else{
                mp.insert(pair<char,int>(t[i],1));
            }
        }

        while (rr < s.size()){
            while (rr < s.size() && !isContain(s.substr(ll,rr+1-ll), mp)){
                rr++;
            }
            if (rr == s.size() && ll == 0){     // 找不到
                return string("");
            }
            while (ll <= rr && isContain(s.substr(ll,rr+1-ll), mp)){
                ll++;
            }
            if (windowSize > rr-ll+2){
                windowSize = rr -ll +2;
                res_left = ll-1;
            }

        }
        return s.substr(res_left, windowSize);
    }
};

int main(){
    Solution s;
    string res = s.findString("a", "a");
    cout <<res<<endl;

    return 0;
}



/*标准答案
字符串的比较完全转化成两个map的比较
class Solution {
public:
    unordered_map <char, int> ori, cnt;

    bool check() {
        for (const auto &p: ori) {
            if (cnt[p.first] < p.second) {
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        for (const auto &c: t) {
            ++ori[c];
        }

        int l = 0, r = -1;
        int len = INT_MAX, ansL = -1, ansR = -1;

        while (r < int(s.size())) {
            if (ori.find(s[++r]) != ori.end()) {
                ++cnt[s[r]];
            }
            while (check() && l <= r) {
                if (r - l + 1 < len) {
                    len = r - l + 1;
                    ansL = l;
                }
                if (ori.find(s[l]) != ori.end()) {
                    --cnt[s[l]];
                }
                ++l;
            }
        }

        return ansL == -1 ? string() : s.substr(ansL, len);
    }
};
*/