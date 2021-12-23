/*
475 供暖器
*/

#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int findRadius(vector<int> &houses, vector<int> &heaters) {

        int min_radius = 0;
        int num_heaters = heaters.size();
        int heat_idx = 0;
        for (int i = 0; i < houses.size(); i++) {
            int radius = abs(houses[i] - heaters[heat_idx]);

            while (heat_idx < num_heaters-1 && radius > abs(houses[i] - heaters[heat_idx+1])) {
                radius = abs(houses[i] - heaters[heat_idx+1]);
                heat_idx++; 
            }
            min_radius = max(min_radius, radius);
        }
        return min_radius; 
    }
};

int main() {
    Solution solu;
    vector<int> houses = {1,1,1,1,1,1,999,999,999,999,999};
    vector<int> heaters = {499,500,501};

    cout << solu.findRadius(houses, heaters)<<"\n";

    return 0;
}