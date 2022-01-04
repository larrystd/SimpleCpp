#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        sort (asteroids.begin(), asteroids.end());
        for (int i = 0; i < asteroids.size(); i++) {
            if (mass >= asteroids[i])
                mass += asteroids[i];
            else 
                return false;
        }
        return true;
    }
};