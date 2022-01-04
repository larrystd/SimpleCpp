/*
输入：hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
输出：true
解释：Alice 手中的牌可以被重新排列为 [1,2,3]，[2,3,4]，[6,7,8]。
*/
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        map<int, int> map_;
        int size = hand.size();
        if (size % groupSize != 0)
            return false;
        int numgroup = size / groupSize;
        for (auto& h : hand) {
            map_[h] ++;
        }

        for (int i = 0; i < numgroup; i++) {
            int start = map_.begin()->first;
            for (int j = 0; j < groupSize; j++) {
                if (!map_.count(start))
                    return false;
                
                if (map_[start] == 1)
                    map_.erase(start);
                else 
                    map_[start] --;
                start++;
            }
        }
        return map_.empty();

    }
};

int main() {
    vector<int> hand = {1,2,3,6,2,3,4,7,8};
    int groupSize = 3;
    Solution solu;
    cout << solu.isNStraightHand(hand, groupSize) << "\n";

    return 0;
}