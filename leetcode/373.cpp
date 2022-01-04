#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int i = 0, j = 0;
        vector<vector<int>> result;

        while() {
            if(i == j) {
                if (nums1[i+1] + nums2[j] < nums1[i]+nums2[j+1]) {
                    result.push_back({nums1[i+1], nums2[j]});
                }else {
                    result.push_back({nums1[i], nums2[j+1]});
                }
            }else if(i < j)
        }
    }
};