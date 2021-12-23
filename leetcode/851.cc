#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> result;
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        vector<vector<int>> adjtable;
        int size = quiet.size();
        adjtable.resize(size);
        for (auto& pair_ : richer) {
            adjtable[pair_[0]].push_back(pair_[1]);
        }

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> sortedquiet;
        for (int i=0; i < size; i++) {
            sortedquiet.push({quiet[i], i});
        }

        result.resize(size, -1);
        while (!sortedquiet.empty()) {
            int smallperson = sortedquiet.top().second;
            sortedquiet.pop();

            dfs(adjtable, smallperson, smallperson);
        }

        return result;
    }

    void dfs(vector<vector<int>>& adjtable, int smallperson, int curperson) {
        if (result[curperson] != -1)
            return;
        result[curperson] = smallperson;

        for (int near : adjtable[curperson]) {
            dfs(adjtable, smallperson, near);
        }
    }
};

int main() {
    vector<vector<int>> richer = {{1,0},{2,1},{3,1},{3,7},{4,3},{5,3},{6,3}};
    vector<int> quiet = {3,2,5,4,6,1,7,0};

    Solution solu;
    auto result = solu.loudAndRich(richer, quiet);
    for (int r : result) {
        cout << r << " ";
    }

    return 0;
}