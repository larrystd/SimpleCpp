#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<vector<int>> tables;

    unordered_set<string> visitedstr;

    int findSubstringInWraproundString(string p) {
        int size = p.size();
        tables.assign(size, vector<int>(size));

        return dfs(0, size-1, p);
    }

    int dfs(int i, int j, const string& p) {
        if (i > j)
            return 0;
        if (visitedstr.count(p.substr(i, j-i+1)))
            return 0;
        visitedstr.insert(p.substr(i, j-i+1));
        if (i == j)
            return 1;
        if (tables[i][j] != 0)
            return tables[i][j];
        
        
        int has_sub = dfs(i+1, j, p) + dfs(i, j-1, p) - dfs(i+1, j-1, p);
        bool issub = true;
        for (int k = i+1; k <= j; k++) {
            if (p[k]-p[k-1] != 1 && !(p[k] == 'a' && p[k-1]=='z')){
                issub = false;
                break;
            }
        }
        issub == true? ++has_sub:has_sub;

        tables[i][j] = issub;
        return has_sub;
    }
};

int main() {
    Solution solu;

    cout << solu.findSubstringInWraproundString("zabcdd") <<endl;

    return 0;
}