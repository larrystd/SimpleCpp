#-*- encoding: utf-8 -*-

from typing import List

class Solution:
    def canPartition(self, nums: List[int]) -> bool:

        sumNum = sum(nums)
        if sumNum % 2 != 0:
            return False
        maxNum = max(nums)
        target = sumNum // 2
        if maxNum > target:
            return False
        length = len(nums)

        dp = [[False] * (target + 1) for _ in range(length)]
        for i in range(length):
            dp[i][0] = True
        
        dp[0][nums[0]] = True  # 初始化

        for i in range(1, length):
            num = nums[i]  # 备选
            for j in range(1, target + 1):
                if j >= num:
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - num]
                else:
                    dp[i][j] = dp[i - 1][j]



        return dp[length-1][target]


s = Solution()
print (s.canPartition([1,5,11,5]))