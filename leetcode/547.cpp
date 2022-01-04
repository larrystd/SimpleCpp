#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int n;
    int findCircleNum(vector<vector<int>>& isConnected) {
        n = isConnected.size();
        vector<bool> visited(n);
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(isConnected, visited, i);
                result++;
            }
        }

        return result;
    }

    void dfs(vector<vector<int>>& isConnected, vector<bool>& visited, int index) {
        //if (visited[index])
        //    return;
        for (int i = 0; i < n; i ++) {
            if (isConnected[index][i] && !visited[i]) {
                visited[i] = true;
                dfs(isConnected, visited, i);
            }
        }
    }
};

int main() {
    Solution solu;
    vector<vector<int>> isConnected =    {{1,1,0},{1,1,0},{0,0,1}};
    cout << solu.findCircleNum(isConnected) <<endl;

    return 0;
}