#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:

    int countDigit(int n) {
        int count = 0;

        while (n) {
            if (n % 10 == 1)
                count++;
            n /= 10;
        }
        return count;
    }
    int countDigitOne(int n) {
        int count = 0;

        for (int i = 1; i <= n; i++) {
            count += countDigit(i);
        }
        return count;
    }
};

int main() {
    Solution s;
    cout << s.countDigitOne(824883294) <<endl;
    return 0;
}