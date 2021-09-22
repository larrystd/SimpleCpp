/// 650 只有两个键的键盘
/*
最初记事本上只有一个字符 'A' 。你每次可以对这个记事本进行两种操作：

Copy All（复制全部）：复制这个记事本中的所有字符（不允许仅复制部分字符）。
Paste（粘贴）：粘贴 上一次 复制的字符。
给你一个数字 n ，你需要使用最少的操作次数，在记事本上输出 恰好 n 个 'A' 。返回能够打印出 n 个 'A' 的最少操作次数。

示例 1：

输入：3
输出：3
解释：
最初, 只有一个字符 'A'。
第 1 步, 使用 Copy All 操作。
第 2 步, 使用 Paste 操作来获得 'AA'。
第 3 步, 使用 Paste 操作来获得 'AAA'。
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    int minSteps(int n) {

        if (n == 1)
            return 0;
        
        vector<int> primes;
        int number = n;

        while(number > 1)
        {
            for(int i=2; i<=number; i++)
            {
                if(number % i==0) //短除法分解质因数, i为质因数
                {
                    number = number/i;
                    primes.push_back(i);    /// 加入因子, 顺序应该从小到大
                    break;
                }
            }
        }
        
        /// 合数
        int result = primes[0]; /// copy + paste, 生成第一个质数次数
        for (int i = 1; i < primes.size(); i++) {
            
            result++;   // 拷贝次数
            result+= primes[i]-1; //粘贴次数
            
            
        }
        return result;
    }
};

int main() {
    Solution solu;
    cout << solu.minSteps(12)<<endl;
    return 0;
}