# -*- encoding:utf-8 -*-

from typing import List

# m(i, W)
def kpack(N:int, wt:List[int], val:List[int], W:int) -> int:
    size = len(wt)
    m = [[0 for i in range(W + 1)] for j in range(N + 1)]

    #i 为选择的物品, j为剩余容量
    for i in range(1, N+1):
        for j in range(1, W+1):
            if wt[i-1] > j:
                m[i][j] = m[i-1][j]
            else:
                m[i][j] = max(m[i-1][j], m[i-1] [j-wt[i-1]]+val[i-1])
    print (m)
    return m[N][W]
    


if __name__ == "__main__":
    N = 3 #地主家有三样东西

    wt = [2,1,3] #每样东西的重量

    val = [4,2,3] #每样东西的价值

    W = 4 #背包可装载重量

    print (kpack(N, wt, val, W))