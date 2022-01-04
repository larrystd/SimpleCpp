/*
leetcode周赛
5865. 访问完所有房间的第一天

你需要访问 n 个房间，房间从 0 到 n - 1 编号。同时，每一天都有一个日期编号，从 0 开始，依天数递增。你每天都会访问一个房间。

最开始的第 0 天，你访问 0 号房间。给你一个长度为 n 且 下标从 0 开始 的数组 nextVisit 。在接下来的几天中，你访问房间的 次序 将根据下面的 规则 决定：

假设某一天，你访问 i 号房间。
如果算上本次访问，访问 i 号房间的次数为 奇数 ，那么 第二天 需要访问 nextVisit[i] 所指定的房间，其中 0 <= nextVisit[i] <= i 。
如果算上本次访问，访问 i 号房间的次数为 偶数 ，那么 第二天 需要访问 (i + 1) mod n 号房间。
请返回你访问完所有房间的第一天的日期编号。题目数据保证总是存在这样的一天。由于答案可能很大，返回对 109 + 7 取余后的结果。
*/
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Solution {
public:
    const int MOD = pow(10,9) + 7;
    int firstDayBeenInAllRooms(vector<int>& nextVisit) {
        int res = 0;
        int n = nextVisit.size(); 
        vector<int> visited(n,0);
        int count = 0;
        int next = 0;

        while (count < n) {
            if (visited[next] == 0)
                count++;
            visited[next]++;
            if (visited[next] % 2 == 0) {
                next = (next + 1) % n;
            }else{
                next = nextVisit[next];
            }
            res = (res+1)%MOD;
        }
        return res-1;
    }
};

int main() {
    Solution s;
    vector<int> nextVisit = {0,0};
    cout << s.firstDayBeenInAllRooms(nextVisit) <<endl;
    return 0;
}

