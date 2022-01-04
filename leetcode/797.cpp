/* 797. 所有可能的路径

给你一个有 n 个节点的 有向无环图（DAG），请你找出所有从节点 0 到节点 n-1 的路径并输出（不要求按特定顺序）

二维数组的第 i 个数组中的单元都表示有向图中 i 号节点所能到达的下一些节点，空就是没有下一个结点了。

译者注：有向图是有方向的，即规定了 a→b 你就不能从 b→a 。
*/
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<int> track;
        
        backtrack(track, 0, graph);

        return res;
    }


    void backtrack(vector<int>& track, int k, vector<vector<int>>& graph) {
        if (k == graph.size() - 1){
            res.push_back(track);
            return;
        }
        if (k == 0)
            track.push_back(0);

        for (int i : graph[k]) {
            track.push_back(i);
            backtrack(track, i, graph);
            track.pop_back();
        }
        if (k == 0)
            track.pop_back();
    }
};


int main() {
    vector<vector<int>> input ={{1,2},{3},{3},{}};

    vector<vector<int>> input2 = {{4,3,1},{3,2,4},{3},{4},{}};

    vector<vector<int>> input3 = {{},{1}};

    Solution s;
    vector<vector<int>> res = s.allPathsSourceTarget(input3);

    for (auto& l : res) {
        for (auto& x : l) {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}