#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        priority_queue<int, vector<int>, greater<int>> prior_nums1;
        priority_queue<int, vector<int>, greater<int>> prior_nums2;
        vector<int> result;
        unordered_map<int, int> nextBigEle;

        for (auto& num : nums1) {
            prior_nums1.push(num);
        }
        for (auto& num : nums2) {
            prior_nums2.push(num);
        }
        while (!prior_nums1.empty() && !prior_nums2.empty()) {
            int num1 = prior_nums1.top();
            prior_nums1.pop();
            while (!prior_nums2.empty()) {
                int num2 = prior_nums2.top();
                if (num2 > num1) {
                    nextBigEle[num1] = num2;
                    break;
                }
                prior_nums2.pop();
            }
        }
        for (auto& num : nums1) {
            if (nextBigEle.count(num)) {
                result.push_back(nextBigEle[num]);
            }else{
                result.push_back(-1);
            }
        }
        return result;

    }
};

int main() {
    vector<int> nums1 = {4,1,2};
    vector<int> nums2 = {1,3,4,2};
    Solution solu;
    vector<int> result = solu.nextGreaterElement(nums1, nums2);
    for (auto& num : result) {
        cout << num << "\n";
    }

    return 0;
}