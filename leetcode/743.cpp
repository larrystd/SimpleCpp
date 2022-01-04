// 743. 网络延迟时间

/*
有 n 个网络节点，标记为 1 到 n。

给你一个列表 times，表示信号经过 有向 边的传递时间。 times[i] = (ui, vi, wi)，其中 ui 是源节点，vi 是目标节点， wi 是一个信号从源节点传递到目标节点的时间。

现在，从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1 

bfs思路超出时间限制
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

    const int INF = INT32_MAX/2;
    int networkDelayTime_dij(vector<vector<int>>& times, int n, int k) {
        vector<bool> book(n+1, false);
        vector<int> dis(n+1, INF);

        /// 邻接矩阵
        vector<vector<int>> graph(n+1,vector<int>(n+1,INF));
        for(int i=1;i<=n;i++)    graph[i][i]=0;
        for(auto e:times)    graph[e[0]][e[1]]=e[2];

        for (int i = 1; i <= n; i++) {
            if (graph[k][i] != INF) {
                dis[i] = graph[k][i];
            }
        }
        book[k] = true;


        for(int i=1;i<n;i++){   // 遍历n-1个节点
            int min_id=0,min_dis=INF;
            for(int j=1;j<=n;j++){
                if(book[j]==false && dis[j]<min_dis){
                    min_dis=dis[j];
                    min_id=j;
                }
            }
            book[min_id]=true;
            for(int j=1;j<=n;j++){
                dis[j] = min(dis[j], dis[min_id]+graph[min_id][j]);
            }
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (dis[i] == INF)
                return -1;
            ans = max(dis[i], ans);
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> x = {{1,2,1},{2,1,3}};
    vector<vector<int>> x2 = {{2,1,1},{2,3,1},{3,4,1}};
    Solution s;
    cout << s.networkDelayTime_dij(x2,4,2) <<endl;
    return 0;
}