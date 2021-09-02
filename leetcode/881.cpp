// leetcode 881 救生艇
/*
第 i 个人的体重为 people[i]，每艘船可以承载的最大重量为 limit。

每艘船最多可同时载两人，但条件是这些人的重量之和最多为 limit。

返回载到每一个人所需的最小船数。(保证每个人都能被船载)。
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());

        int num = 0;
        int left = 0;
        int right = people.size() - 1;

        while (left <= right) {
            if (left == right)
                left++;
            if (people[left] + people[right] > limit) {
                right--;
            }
            else {
                left++;
                right--;
            }
            num++;
        }
        return num;
    }
};

int main () {
    vector<int> people = {5,1,4,2};
    Solution s;

    cout<< s.numRescueBoats(people, 6)<<endl;
    return 0;
}