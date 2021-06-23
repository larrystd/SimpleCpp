"""
给定一个非空字符串 s 和一个包含非空单词的列表 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。
拆分时可以重复使用字典中的单词。

输入: s = "leetcode", wordDict = ["leet", "code"]
输出: true
解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。

方法一：动态规划
初始化 dp=[False,⋯,False]，长度为 n+1。n 为字符串长度。dp[i] 表示 s 的前 i 位是否可以用 wordDict 中的单词表示。

初始化 dp[0]=True，空字符可以被表示
遍历字符串的所有子串，遍历开始索引 i，遍历区间 [0,n):

若 dp[i]=True 且 s[i,⋯,j) 在 wordlistwordlist 中：dp[j]=True。

其中，dp[i]=True 说明 s 的前 i 位可以用 wordDict 表示，则 s[i,⋯,j) 出现在 wordDict 中，说明 s 的前 j 位可以表示。

返回 dp[n]


记忆化回溯
"""

from typing import List

"""
typing模块的作用：

类型检查，防止运行时出现参数和返回值类型不符合。
作为开发文档附加说明，方便使用者调用时传入和返回参数类型。
该模块加入后并不会影响程序的运行，不会报正式的错误，只有提醒。

from typing import List, Tuple, Dict
"""
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:       
        n=len(s)
        dp=[False]*(n+1)
        dp[0]=True
        for i in range(n):
            for j in range(i+1,n+1):    # 1~n
                if(dp[i] and (s[i:j] in wordDict)):
                    dp[j]=True
        return dp[-1]
    
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        import functools
        @functools.lru_cache(None)
        def back_track(s):
            if(not s):
                return True
            res=False
            for i in range(1,len(s)+1):
                if(s[:i] in wordDict):
                    res=back_track(s[i:]) or res
            return res
        return back_track(s)


if __name__ == "__main__":
    s = Solution()
    print (s.wordBreak("leetcode", ["leet", "code"]) )

    s = "123"
    print (s[1:3])