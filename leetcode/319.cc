/*
leetcode 319 灯泡开关
初始时有 n 个灯泡处于关闭状态。第一轮，你将会打开所有灯泡。接下来的第二轮，你将会每两个灯泡关闭一个。

第三轮，你每三个灯泡就切换一个灯泡的开关（即，打开变关闭，关闭变打开）。第 i 轮，你每 i 个灯泡就切换一个灯泡的开关。直到第 n 轮，你只需要切换最后一个灯泡的开关。

找出并返回 n 轮后有多少个亮着的灯泡。
*/
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    int bulbSwitch(int n) {
        // 因数个数为奇数才能最终灯是亮的
        int result = 0; // 第一个灯泡肯定亮
        for (int i = 1; i <= n; i++) {
            int num_factor = 0;
            for (int j = 1; j <= i; j++) {
                if (i % j == 0)
                    ++num_factor;
            }
            result = num_factor%2 == 0 ? result : result+1;
        }
        return result;
    }

    int bulbSwitch_v2(int n) {
        // 既然因数个数为奇数才能最终灯是亮的, 因数个数为奇数的数必然是完全平方数
        int result = 0;
        for (int i = 1; i <= sqrt(n) + 1; i++) {
            if (i*i <= n) {
                result++;
            }
        }
        return result;
    }
};

int main() {
    Solution solu;
    cout << solu.bulbSwitch_v2(16)<<endl;

    return 0;
}