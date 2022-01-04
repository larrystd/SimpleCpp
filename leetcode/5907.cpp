#include <unordered_map>
#include <iostream>
#include <string.h>

using namespace std;

class Solution {
public:
    bool isBeautifulNumber(int n) {
        unordered_map<int ,int> map_;
        while (n) {
            int temp = n % 10;
            if (map_.count(temp))
                map_[temp]++;
            else
                map_[temp]  = 1;
            n /= 10;
        }
        for (auto& e : map_) {
            if (e.second != e.first)
                return false;
        }
        return true;
    }

    bool check(int num)
    {
        int xf[10];
        memset(xf, 0, sizeof(xf));
        while (num != 0)
        {
            int x = num % 10;
            xf[x] ++;
            num /= 10;
        }
        for (int x = 0; x < 10; x ++)
        {
            if (xf[x] != 0 && x != xf[x])
            {
                return false;
            }
        }
        return true;
    }
    int nextBeautifulNumber(int n) {
        string n_s = to_string(n);
        int n_bit = n_s.size();
        int n_max = 0;
        int time = 1;
        for (int i = 0; i < n_bit; i++) {
            n_max += n_bit * time;
            time *= 10;
        }
        int m;
        if (n < n_max) {
            m = n+1;
        }else {
            m = time;
        }

        while (!check(m)) {
            m++;
        }
        return m;
    }
};

int main() {
    Solution solu;
    cout << solu.nextBeautifulNumber(1000000) <<endl;
    return 0;
}