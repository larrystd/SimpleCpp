#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> graph;
    vector<int> weight;
    int countHighestScoreNodes(vector<int>& parents) {
        int num = parents.size();
        graph.resize(num);
        int root;
        for (int i = 0; i < num; i++) {
            if (parents[i] != -1) {
                graph[i].push_back(parents[i]);
                graph[parents[i]].push_back(i);
            }else{
                root = i;
            }
        }
        weight.resize(num); // 每个节点的权重(子树大小)

        dfs(root, -1);

        long long result = 0;  // 根节点权重
        int result_num = 0;

        for (int i = 0;i < num; i++) {
            int son_num = 0;
            int parent_num;
            long long node_value = 1;
            for (auto& son : graph[i]) {
                if (son != parents[i]) {
                    node_value*= weight[son];
                    son_num += weight[son];
                }
            }
            parent_num = num - 1 -son_num;
            if (parent_num > 0)
                node_value*=parent_num;
            if (node_value > result) {
                result_num = 1;
                result = node_value;
            }
            else if (node_value == result)
                result_num++;
        }

        return result_num;
    }

    int dfs(int node ,int fa) {
        
        int num_node = 0;
        for (auto& son : graph[node]) {
            if (son != fa) {
                num_node+= dfs(son, node);
            }
        }
        weight[node] = num_node+1;
        return num_node+1;
    }
};

int main() {
    Solution solu;

    vector<int> parents = {-1,2,0};
    cout << solu.countHighestScoreNodes(parents) <<endl;

    return 0;
}