#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        int nodenum =  favorite.size();
        vector<vector<int>> loved(nodenum);
        // 它被爱着
        for (int i = 0; i < favorite.size(); i++) {
            loved[favorite[i]].push_back(i);
        }

        int result = 0;
        vector<int> visited(nodenum);
        for (int i = 0; i < nodenum; i++) {
            int pathlen = 1;
            visited.assign(nodenum, 0);
            visited[i] = 1;
            if (dfs(favorite, favorite[i], i, pathlen, visited)) {
                if (pathlen == 2) {
                    int dep = 0;
                    for (int near : loved[i]) {
                        if (near != favorite[i])
                            dfsDep(near, loved, 1, dep);
                    }
                    pathlen += dep;
                    dep = 0;
                    for (int near : loved[favorite[i]]) {
                        if (near != i)
                            dfsDep(near, loved, 1, dep);
                    }
                    pathlen += dep;
                    
                }
                result = max(result, pathlen);                    
           }
       }

       return result;
    }

    void dfsDep(int cur, vector<vector<int>> loved, int dep, int&  result) {
        result = max(result, dep);
        for (int i : loved[cur]) {
            dfsDep(i, loved, dep+1, result);
        }
    }

    bool dfs(const vector<int>& graph, int curnode, int startnode, int& pathlen,  vector<int>& visited) {
        if (graph[curnode] == startnode) {
            pathlen++;
            return true;
        }
        visited[curnode] = 1;
        if (!visited[graph[curnode]]) {
            if (dfs(graph, graph[curnode], startnode, ++pathlen, visited))
                return true;
        }
        return false;
    }
};

int main() {
    vector<int> favorite = {1,0,0,2,1,0,5,6};
    Solution solu;
    cout << solu.maximumInvitations(favorite) << "\n";

    return 0;
}