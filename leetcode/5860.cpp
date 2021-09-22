// 5860. 从双倍数组中还原原数组

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        int n = changed.size();

        //vector<int> use_map(n, 0);
        map<int, int> use_map;
        vector<int> result;
        set<int> result_set;
        bool is_double = true;

        for (int i : changed) {
            if (use_map.count(i))
                use_map[i] ++;
            else
                use_map[i] = 1;
        }

        for (auto&& it : use_map) {
            while (it.second != 0) {
                if (!use_map.count(it.first * 2) || use_map[it.first * 2] <= 0)
                    return vector<int>();
                
                use_map[it.first * 2] --;
                it.second--;
                result_set.insert(it.first);
            }
        }

        for (auto&& it : use_map) {
            if (it.second != 0)
                return vector<int>();
        }

        for (auto&& it :result_set){
            result.push_back(it);
        }

        return result;
    }
};

int main() {
    vector<int> changed = {6,3,0,1};
    Solution solu;

    vector<int> result = solu.findOriginalArray(changed);

    for (auto&& it : result)    {
        cout << it << endl;
    }
    return 0;
}