#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        sort(ages.begin(), ages.end());

        int result = 0;
        for (int i = 1; i < ages.size(); i++) {
            for (int j = i-1; j>=0; j--) {
                if (ages[j] <= 0.5*ages[i] + 7)
                    break;
                result++;
            } 
        }

        return result;
    }
};

int main() {
    Solution solu;
    vector<int> ages{16, 16};
    cout << solu.numFriendRequests(ages) << "\n";

    return 0;
}