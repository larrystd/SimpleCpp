#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();   // 节点个数

        // 1.初始化队列及标记数组，存入起点
        queue< tuple<int, int, int> > q; // 三个属性分别为 idx, mask, dist
        vector<vector<int>> vis(n, vector<int>(1 << n)); // 节点编号及当前状态
        for(int i = 0; i < n; i++) {
            q.push({i, 1 << i, 0}); // 存入起点，起始距离0，标记
            vis[i][1 << i] = 1;
        }

        // 开始搜索
        while(!q.empty()) {
            // auto [cur, mask, dist] = q.front(); // 弹出队头元素
            int cur = std::get<0>(q.front());
            int mask = std::get<1>(q.front());
            int dist = std::get<2>(q.front());
            q.pop();

            // 节点完全访问完毕
            if(mask == (1 << n) - 1) return dist;

            // 扩展
            for(int x : graph[cur]) {
                int nextmask = mask | (1 << x); // 访问了x节点， 修改mask
                if(!vis[x][nextmask]) {
                    q.push({x, nextmask, dist + 1});
                    vis[x][nextmask] = 1;
                }
            }
        }
        return 0;
    }
};

class SolutionV2 {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();   // 节点个数

        // 1.初始化队列及标记数组，存入起点
        queue< tuple<int, int, int> > q; // 三个属性分别为 idx, mask, dist
        vector<vector<int>> vis(n, vector<int>(1 << n)); // 节点编号及当前状态
        //for(int i = 0; i < n; i++) {
        //    q.push({i, 1 << i, 0}); // 存入起点，起始距离0，标记
        //    vis[i][1 << i] = 1;
        //}
        q.push({0, 1, 0}); // 存入起点，起始距离0，标记
        vis[0][1] = 1;

        // 开始搜索
        while(!q.empty()) {
            // auto [cur, mask, dist] = q.front(); // 弹出队头元素
            int cur = std::get<0>(q.front());
            int mask = std::get<1>(q.front());
            int dist = std::get<2>(q.front());
            q.pop();

            // 节点完全访问完毕
            if(mask == (1 << n) - 1) return dist;

            // 扩展
            for(int x : graph[cur]) {
                int nextmask = mask | (1 << x); // 访问了x节点， 修改mask
                if(!vis[x][nextmask]) {
                    q.push({x, nextmask, dist + 1});
                    vis[x][nextmask] = 1;
                }
            }
        }
        return 0;
    }
};

int main() {
    vector<vector<int>> graph =  {{1,2,3},{0},{0},{0}};
    Solution solu;

    cout << solu.shortestPathLength(graph)<<"\n";
    return 0;
}