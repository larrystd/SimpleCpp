#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<int>> dp;
    //string pat;
    void KMP(string pat) {
    /// 基于模式串得到转移dp
    /// 
        //this->pat = pat;
        int M = pat.size();
        // dp[状态][字符] = 下个状态
        dp.resize(M, vector<int>(256, 0));
        // 初始化,状态0遇到pat[0]跳转到1, 其他还是0
        dp[0][pat[0]] = 1;  
        // 影子状态 X 初始为 0
        int X = 0;
        // 构建状态转移图
        for (int j = 1; j < M; j++) {
            for (int c = 0; c < 256; c++)
                /// 先设置匹配失败跳转到dp[X][c]
                dp[j][c] = dp[X][c];
            /// 匹配成功则跳转到j+1
            dp[j][pat[j]] = j + 1;
            // 更新影子状态
            /// X遇到pat[j]的状态,dp[X]已经计算过了
            X = dp[X][pat[j]];
        }
    }
    /// 基于模式串的匹配
    int strStr(string txt, string pat){
        int M = pat.size();
        int N = txt.size();
        // pat 的初始态为 0
        KMP(pat);
        int j = 0;
        /// 计算N次
        for (int i = 0; i < N; i++) {
            // 计算 pat 的下一个状态
            j = dp[j][txt[i]];
            // 到达终止态，返回结果
            if (j == M) return i - M + 1;
        }
        // 没到达终止态，匹配失败
        return -1;
    }
};


int main() {
    string str = "hello";
    string pat = "ll";

    Solution solu;
    cout << solu.strStr(str, pat)<<endl;
    return 0;
}