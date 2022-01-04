#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<int> max_prev_cost(n+1);
        vector<int> in_degree(n+1);
        vector<vector<int>> to_node(n+1);
        vector<bool> visited(n+1);

        vector<int> node_time(n+1);
        for (int i = 0; i < n; i++) {
            node_time[i+1] = time[i];
        }

        int result = 0;

        for (auto& relation : relations) {
            in_degree[relation[1]] ++;
            to_node[relation[0]].push_back(relation[1]);
        }

        queue<int> q;   
        for (int i = 1; i <= n; i++)    // 入度为0的节点入队
            if (in_degree[i] == 0)
                q.push(i);

        while (!q.empty()) {
            int u = q.front();	
            q.pop();
            node_time[u] += max_prev_cost[u];    // 到节点i的最小花费
            result = max(node_time[u], result);
            for (auto& next : to_node[u]) {// i指向的地方
                max_prev_cost[next] = max(max_prev_cost[next], node_time[u]);   // 到达to节点的花费
                in_degree[next]--;			
                if (in_degree[next] == 0)		//顶点v的入度减为0则入队
                    q.push(next);
            }
        }
        return result;
    }
};

int main() {
    vector<vector<int>> relations = {{2,1}};
    vector<int> time = {10000, 10000};
    int n = 2;

    Solution solu;
    cout << solu.minimumTime(n, relations, time)<<endl;

    return 0;
}