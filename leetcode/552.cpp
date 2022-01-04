// 552. 学生出勤记录 II

/*
可以用字符串表示一个学生的出勤记录，其中的每个字符用来标记当天的出勤情况（缺勤、迟到、到场）。记录中只含下面三种字符：
'A'：Absent，缺勤
'L'：Late，迟到
'P'：Present，到场
如果学生能够 同时 满足下面两个条件，则可以获得出勤奖励：

按 总出勤 计，学生缺勤（'A'）严格 少于两天。
学生 不会 存在 连续 3 天或 连续 3 天以上的迟到（'L'）记录。
给你一个整数 n ，表示出勤记录的长度（次数）。请你返回记录长度为 n 时，可能获得出勤奖励的记录情况 数量 。答案可能很大，所以返回对 109 + 7 取余 的结果。
*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
public:
    int res = 0;
    const int MOD = pow(10,9) + 7;
    vector<vector<vector<int>>> cache;


    int checkRecord(int n) {
        vector<char> track;
        vector<char> list = {'A', 'L', 'P'};
        cache.resize(n+1, vector<vector<int>>(2, vector<int>(3, 0)));

        return backtrack_mm(list, track, n, 0, 0);

        
    }
    void backtrack(vector<char>& list, vector<char>& track, int k,int A, int L) {
        if (k == 0){
            res++;
            res %= MOD;
        }
        
        int ans = 0;
        for (char c : list) {
            if (L == 2 && c == 'L' || A == 1 && c == 'A') {
                continue;
            }
            else{
                track.push_back(c);
                // 备忘录的状态, L应该是连续状态
                if (c == 'A')
                    backtrack(list, track, k-1, A+1, 0);
                else if (c == 'L')
                    backtrack(list, track, k-1, A, L+1);
                else
                    backtrack(list, track, k-1, A, 0);
                track.pop_back();
            }   
        }
    }


    int backtrack_mm(vector<char>& list, vector<char>& track, int k,int A, int L) {
        if (k == 0){
            return 1;
        }

        if (cache[k][A][L] != 0){

            return cache[k][A][L];
        }
        
        int ans = 0;
        for (char c : list) {
            if (!(L == 2 && c == 'L' || A == 1 && c == 'A')) {
            
                track.push_back(c);
                // 备忘录的状态, L应该是连续状态
                if (c == 'A')
                    ans =  (ans + backtrack_mm(list, track, k-1, A+1, 0)) % MOD;
                else if (c == 'L')
                    ans = (ans + backtrack_mm(list, track, k-1, A, L+1)) % MOD;
                else
                    ans = (ans + backtrack_mm(list, track, k-1, A, 0) ) % MOD;
                track.pop_back();
            }   
        }

        cache[k][A][L] = ans;
        return ans;
    }


    bool isReasonable(const vector<char>& track, const char c) {
        int count_A = 0;
        int n = track.size();
        for (int i = 0; i < track.size(); i++) {
            if (track[i] == 'A')
                count_A++;
        }

        if (c == 'A' && count_A >= 1)
            return false;
        if (c != 'A' && count_A >= 2)
            return false;
        if (n >= 2 && c == 'L' && track[n-1] == 'L' && track[n-2] == 'L')
            return false;
        return true;
    }
};


int main() {
    Solution s;
    cout << s.checkRecord(10101) <<endl;

    return 0;
}