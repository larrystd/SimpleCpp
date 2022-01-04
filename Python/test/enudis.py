import numpy as np

a = [3  ,1  ,3   ,1 ,3   ,1]
b = [4  ,1.5  ,2  ,2.8  ,2 , 1]

vec1 = np.array(a)
vec2 = np.array(b)

# 方法一
distance= np.sqrt(np.sum(np.square(vec1-vec2)))

# method 2 
dist = np.linalg.norm(vec1-vec2)

print (distance)
print (1/(1+dist))
