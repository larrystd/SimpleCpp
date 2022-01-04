import numpy as np

a  = np.array([[1, 1, 1], [1,2,4], [1,3,9]])  # 初始化一个非奇异矩阵(数组)
print(np.linalg.inv(a))  # 对应于MATLAB中 inv() 函数

# 矩阵对象可以通过 .I 更方便的求逆
A = np.matrix(a)

B = np.array([215,216,217])
print(A.I)
print (B)
print (np.dot(A.I, B))


import numpy as np
A = np.mat('1,1,1,1; 1,2,4,8; 1,3,9,27; 1,4,16,64')    # 构造系数矩阵 A
b = np.mat('8,16,32,64').T       # 构造转置矩阵 b （这里必须为列向量）
r = np.linalg.solve(A,b)  # 调用 solve 函数求解
print (r)


def f(x):
    return (x*85+x**2*219+x**3*150) % 223

for i in range(1,6):
    print (f(i))