/*
丑数

给你一个整数 n ，请你判断 n 是否为 丑数 。如果是，返回 true ；否则，返回 false 。

丑数 就是只包含质因数 2、3 和/或 5 的正整数。

思路，依次循环除2,3,5，如果最后值为1则是整数
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static bool uglyNumber (int number) {
        vector<int> nums = {2,3,5};

        for (int num : nums) {
            while (number % num == 0){
                number /= num;
            }
        }

        return number == 1;
    }
};

int main() {
    int ans = Solution().uglyNumber(-2);
    cout << ans<<endl;

    return 0;
}