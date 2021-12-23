#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        int start = 0;
        int end = 2*k+1;
        int size = nums.size();
        if (size < end) {
            return vector<int> (size, -1);
        }
        vector<int> result(k, -1);
        long windowsum = accumulate(nums.begin(), nums.begin()+end, (long)0);
        result.push_back(windowsum / (2*k+1));
        while (end < size) {

            windowsum -= nums[start];
            windowsum += nums[end];
            result.push_back(windowsum / (2*k+1));
            end++;
            start++;
        }
        for (int i = 0; i < k; i++) {
            result.push_back(-1);
            start++;
        }
        return result;
    }
};

int main() {
    vector<int> nums = {8};
    int k = 100;
    Solution solu;
    vector<int> result= solu.getAverages(nums, k);
    for (int e : result) {
        cout << e << " ";
    }
    return 0;
}