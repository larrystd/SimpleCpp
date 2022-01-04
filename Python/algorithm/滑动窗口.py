from typing import List

class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:

        target = [0]*26
        current = [0]*26    # 当前滑动窗口

        ans = []

        num_char = len(set(p))

        for c in p:
            target[ord(c)-ord('a')] += 1

        left,right = 0,0
        valid_c = 0 

        while right < len(s):
            right_c_index = ord(s[right]) - ord('a')
            current[right_c_index] += 1

            if current[right_c_index] != 0 and current[right_c_index] == target[right_c_index]:
                valid_c +=1
            
            right += 1
            while valid_c == num_char:
                left_c_index = ord(s[left])-ord('a')
                if right - left  == len(p):
                    ans.append(left)

                current[left_c_index] -= 1
                if current[left_c_index] != 0 and  target[left_c_index] > current[left_c_index]:

                    valid_c -=1
                left += 1
        return ans

s = Solution()
print(s.findAnagrams('cbaebabacd','abc'))
        