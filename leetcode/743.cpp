// 743. 网络延迟时间

/*
有 n 个网络节点，标记为 1 到 n。

给你一个列表 times，表示信号经过 有向 边的传递时间。 times[i] = (ui, vi, wi)，其中 ui 是源节点，vi 是目标节点， wi 是一个信号从源节点传递到目标节点的时间。

bfs思路不对
必须用最短路算法才行
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<vector<int>>> m;
        for (auto l : times) {
            m[l[0]].push_back(vector<int>{l[1], l[2]});
        }

        int cover = 0;
        int time = 0;
        queue<vector<int>> q;
        q.push(vector<int>{k, 0});

        vector<int> mark(n+1, 0);

        // 环

        while (!q.empty()) {
            vector<int> now = q.front();
            if (mark[now[0]] == 0 && m.count(now[0])){
                for (auto n : m[now[0]]) {
                    if (mark[now[0]] == 0)
                    q.push(vector<int>{n[0], now[1]+n[1]});
                }
            }

            cover++;
            time = max(time, now[1]);
            mark[now[0]] = 1;
            q.pop();
        }
        if (cover < n)
            return -1;
        return time;
    }
};

int main() {
    vector<vector<int>> x = {{1,2,1},{2,1,3}};
    Solution s;
    cout << s.networkDelayTime(x,2,2) <<endl;
    return 0;
}