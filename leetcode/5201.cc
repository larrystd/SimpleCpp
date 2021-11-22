// leetcode 5201植物浇水
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int wateringPlants(vector<int>& plants, int capacity) {
        int left = capacity;
        int sum_steps = 0;
        for (int i = 0; i < plants.size(); i++) {
            if (plants[i] > left) {
                sum_steps += i; // 取水
                left = capacity;

                sum_steps += (i+1);
                left -= plants[i];
            }else {
                left -= plants[i];
                sum_steps ++;
            }

        }
        return sum_steps;
    }
};

int main() {
    Solution solu;
    vector<int> plants = {7,7,7,7,7,7,7};
    int capaity = 8;
    cout << solu.wateringPlants(plants, capaity);
    return 0;
}