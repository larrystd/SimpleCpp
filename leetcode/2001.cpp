#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;


class Solution {
public:
    int gcd (int a, int b) {
        if (b == 0)
            return a;
        else
            return gcd(b, a%b);
    }
    long long interchangeableRectangles(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        if (n < 2)
            return 0;
        // 多重hashmap
        unordered_map<int, unordered_map<int, long long>> use_map;

        for (auto&& rect : rectangles) {
            int mod = gcd (rect[0], rect[1]);
            rect[0] = rect[0] / mod;
            rect[1] = rect[1] / mod;
            use_map[rect[0]][rect[1]]++;
        }
        long long res = 0;
        for (auto&& m : use_map) {
            for (auto&& iter : m.second)
                res += (iter.second * (iter.second-1))/2;
        }
        return res;
    }
};

int main() {
    vector<vector<int>> rects = {{5,8},{3,6},{10,20},{15,30}};

    Solution solu;
    cout << solu.interchangeableRectangles(rects)<<endl;

    return 0;
}