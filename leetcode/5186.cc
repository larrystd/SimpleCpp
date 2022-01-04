#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class RangeFreqQuery {
public:
    RangeFreqQuery(vector<int>& arr) {
        
        for (int i = 0; i < arr.size(); i++) {
            tables[arr[i]].insert(i);
        }
        
    }
    
    int query(int left, int right, int value) {

        int result = 0;
        
        //vector<int> idx(tables[value].begin(), tables[value].end());
        //if (left < 0 || right >= idx.size())
        //    return 0;
        //int pos_left = lower_bound(tables[value].begin(),tables[value].end(),left) - tables[value].begin(); // 大于等于left
        //int pos_right = upper_bound(tables[value].begin(),tables[value].end(),right) - tables[value].begin();    // 大于right
        int pos_left = tables[value].lower_bound(left) - tables[value].begin();
        int pos_right = tables[value].upper_bound(right) - tables[value].begin();
        return pos_right-pos_left;
    }
private:
    unordered_map<int, set<int>> tables;
};

int main() {
    vector<int> arr = {12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56};
    RangeFreqQuery rangeFreqQuery(arr);
    cout << rangeFreqQuery.query(1, 2, 4) << " "; // 返回 1 。4 在子数组 [33, 4] 中出现 1 次。
    cout << rangeFreqQuery.query(0, 11, 33); // 返回 2 。33 在整个子数组中出现 2 次。

    return 0;
}