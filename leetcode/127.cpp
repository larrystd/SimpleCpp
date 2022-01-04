#include <set>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

class Solution {
public:
    string s, e;
    set<string> set_str;
    int ladderLength(string _s, string _e, vector<string> ws) {
        s = _s;
        e = _e;
        // 将所有 word 存入 set，如果目标单词不在 set 中，说明无解
        for (auto& w : ws) set_str.insert(w);
        if (!set_str.count(e)) return 0;
        int ans = bfs();
        return ans == -1 ? 0 : ans + 1;
    }

    int bfs() {
        // d1 代表从起点 beginWord 开始搜索（正向）
        // d2 代表从结尾 endWord 开始搜索（反向）
        queue<string> d1;
        queue<string> d2;
        /*
         * m1 和 m2 分别记录两个方向出现的单词是经过多少次转换而来
         * e.g. 
         * m1 = {"abc":1} 代表 abc 由 beginWord 替换 1 次字符而来
         * m2 = {"xyz":3} 代表 xyz 由 endWord 替换 3 次字符而来
         */
        map<string, int> m1, m2;
        d1.push(s);
        m1[s] = 0;
        d2.push(e);
        m2[e] = 0;
        
        /*
         * 只有两个队列都不空，才有必要继续往下搜索
         * 如果其中一个队列空了，说明从某个方向搜到底都搜不到该方向的目标节点
         * e.g. 
         * 例如，如果 d1 为空了，说明从 beginWord 搜索到底都搜索不到 endWord，反向搜索也没必要进行了
         */
        while (!d1.empty() && !d2.empty()) {
            int t = -1;
            // 为了让两个方向的搜索尽可能平均，优先拓展队列内元素少的方向
            if (d1.size() <= d2.size()) {
                t = update(d1, m1, m2);
            } else {
                t = update(d2, m2, m1);
            }
            if (t != -1) return t;
        }
        return -1;
    }

    // update 代表从 deque 中取出一个单词进行扩展，
    // cur 为当前方向的距离字典；other 为另外一个方向的距离字典
    int update(queue<string>& q, map<string, int>& cur, map<string, int>& other) {
        // 获取当前需要扩展的原字符串
        string str = q.front();
        q.pop();
        int n = str.size();

        // 枚举替换原字符串的哪个字符 i
        for (int i = 0; i < n; i++) {
            // 枚举将 i 替换成哪个小写字母
            string sub(str);
            for (int j = 0; j < 26; j++) {
                // 替换后的字符串
                sub[i] = 'a' + j;
                if (set_str.count(sub)) {
                    // 如果该字符串在「当前方向」被记录过（拓展过），跳过即可
                    if (cur.count(sub)) continue;

                    // 如果该字符串在「另一方向」出现过，说明找到了联通两个方向的最短路
                    if (other.count(sub)) {
                        return cur[str] + 1 + other[sub];
                    } else {
                        // 否则加入 deque 队列
                        q.push(sub);
                        cur[sub] = cur[str]+1;
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    string bw("hit");
    string ew("cog");
    vector<string> word_list = {"hot","dot","dog","lot","log","cog"};

    Solution solu;
    cout << solu.ladderLength(bw, ew, word_list) <<endl;

    return 0;
}