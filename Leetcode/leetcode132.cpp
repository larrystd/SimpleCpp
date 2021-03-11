/*
 * @Author: your name
 * @Date: 2021-03-08 16:14:50
 * @LastEditTime: 2021-03-08 17:01:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Leetcode/leetcode132.cpp
 */
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class Solution {
public:
    int judgeStr(string s,int i,int j){     // 判断字符串是否为回文串
        //int i = 0;
        // int j = s.size() - 1;
        while (i <= j){
            if ( s[i] != s[j] )
                return false;
            i++;
            j--;
        }
        return true;
    }
    int minCut(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, true));

        vector<int> res(n, n);
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i+1; j < n; j++)
            {
                dp[i][j] = judgeStr(s, i, j);       // 判断子字符串是否为回文串
            }
        }

        for (int i = 0; i < n; i++){
            if (dp[0][i])
                res[i] = 0;     // 如果是回文串，不用切分
            else
            {
                for (int j = 0; j < i; j++)
                {
                    if (dp[j+1][i])
                        res[i] = min(res[j]+1,res[i]);
                }   
            }
        }
        return res[n-1];

    }

};

int main(){
    Solution *s = new Solution();
    cout << s->minCut("b")<<endl;
    return 0;
}

