#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
public:
    bool checkPerfectNumber(int num) {
        int result = 1;
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                result += i;
                result += num/i;
            }
        }

        return num == result;
    }
};