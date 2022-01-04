#include <vector>
#include <iostream>
#include <queue>
#include <fmt/format.h>

using namespace std;

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> priorque;
        for (int num : nums) {
            priorque.push(make_pair(num, 0));
        }
        int sum = 0;
        int i = 0;
        while (i < k) {    //处理负数
            int tope = priorque.top().first;
            if (tope >=0 )
                break;
            if (tope < 0) {
                sum -= tope;    // 负数变正数
                priorque.pop();
                priorque.push(make_pair(-tope,1));
                i++;
            }
        }
        if ((k - i)%2 == 1) {
            int tope = priorque.top().first;
            int time = priorque.top().second;
            if (time == 1)
                sum = sum - 2*tope;
            else
                sum = sum - tope;
            priorque.pop();
        }

        while (!priorque.empty()) {
            int tope = priorque.top().first;
            int time = priorque.top().second;
            if (time == 0) 
                sum += tope;
            priorque.pop();
        }

        return sum;
    }
};

int main() {
    Solution solu;
    vector<int> nums = {-8,3,-5,-3,-5,-2};
    fmt::print("Hello, {0}, {0}", solu.largestSumAfterKNegations(nums, 6));

    return 0;
}