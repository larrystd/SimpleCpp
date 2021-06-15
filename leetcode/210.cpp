/*
现在你总共有 n 门课需要选，记为 0 到 n-1。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]

给定课程总量以及它们的先决条件，返回你为了学完所有课程所安排的学习顺序。

输入: 4, [[1,0],[2,0],[3,1],[3,2]]
输出: [0,1,2,3] or [0,2,1,3]

拓扑排序，一种广度优先搜索

从入度为0的节点开始，访问后删除与该点的边。
若能访问到全部节点，说明可以实现拓扑排序
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int num_node = numCourses;
        vector<int> num_degree(num_node, 0);
        vector<int> topo_list;

        vector<vector<int>> adj_table;
        adj_table.resize(num_node);
        // 1->0
        for (int i = 0; i < prerequisites.size(); i++) {
            adj_table[prerequisites[i][1]].push_back(prerequisites[i][0]);
            num_degree[prerequisites[i][0]] ++;
        }

        queue<int> q;
        int access_num = 0;
        for (int i = 0; i < num_node; i++){
            if (num_degree[i] == 0){
                q.push(i);
                topo_list.push_back(i);
            }
                
        }

        while (!q.empty()){
            int node = q.front();
            for (int i = 0; i < adj_table[node].size(); i++) {
                num_degree[adj_table[node][i]] --;

                if (num_degree[adj_table[node][i]] == 0) {
                    q.push(adj_table[node][i]);
                    topo_list.push_back(adj_table[node][i]);
                }
            }
            q.pop();
        }

        return topo_list.size() == num_node ? topo_list : vector<int>() ;
    }
};

int main() {
    vector<vector<int>> vec {{1,0},{2,0},{3,1},{3,2}};

    Solution s;
    vector<int> res = s.findOrder(4, vec);

    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }

    return 0;
}