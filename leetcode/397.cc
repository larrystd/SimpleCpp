/*
leetcode 397
给定一个正整数 n ，你可以做如下操作：

如果 n 是偶数，则用 n / 2替换 n 。
如果 n 是奇数，则可以用 n + 1或n - 1替换 n 。
n 变为 1 所需的最小替换次数是多少？
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    unordered_map<long, int> mtable;
    int integerReplacement(int n) {
        return dfs(long(n));
    }
    
    int dfs(long n) {
        if (n == 1)
            return 0;
        if (mtable.count(n))
            return mtable[n];
        int ans;
        if (n % 2)
            ans = min(dfs(n-1), dfs(n+1))+1;
        else
            ans = dfs(n/2)+1;
        mtable[n] = ans;
        return ans;
    }
};

int main() {
    Solution solu;
    cout << solu.integerReplacement(89)<<endl;

    return 0;
}