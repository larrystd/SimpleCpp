import math

class Vector:
    def __init__(self, x=0, y=0):
         self.x = x
         self.y = y
    
    #def __repr__(self):
    #    return 'Vector(%r, %r)' % (self.x, self.y)
    
    def __add__(self, other):
        x = self.x + other.x
        y = self.y + other.y
        return Vector(x,y)

v1 = Vector(1,2)
v2 =  Vector(2,3)
v3 = v1+v2

print(v3)

def sum_sech(x):
    sum = 0
    for i in range(1,x+1):
        sum += 2/(math.exp(i) + math.exp(-i))

    return sum

for i in range(1,7):
    print (sum_sech(i))

print (2/(math.exp(4) + math.exp(-4)))


from scipy.optimize import fsolve

def func(i):
    x, y, z = i[0], i[1], i[2]
    return [
    x + 2 * y + 3 * z - 6,
                5 * (x ** 2) + 6 * (y ** 2) + 7 * (z ** 2) - 18,
                9 * (x ** 3) + 10 * (y ** 3) + 11 * (z ** 3) - 30
            ]
def func2(i):
    x = i[0]
    return [2*2/(math.exp(-x)+math.exp(x)) + 3 * ((math.exp(x)-math.exp(-x))/(math.exp(-x)+math.exp(x)))**2 - 3]

r = fsolve(func,[0, 0, 0])

def func3(x):
    return 2*2/(math.exp(-x)+math.exp(x)) + 3 * ((math.exp(x)-math.exp(-x))/(math.exp(-x)+math.exp(x)))**2 - 3

def func4(x):
    return -1+6/(math.exp(-x)+math.exp(x))

r2 = fsolve(func2, [1])
print (r2)

print (func3(r2[0]))



r4 = fsolve(func4, 1)

print (r4)
print (func3(r4))
import numpy as np
X = np.arange(-5,5,0.01)
Y = np.arange(-5,5,0.01)

#Y = [func3[i] for i in X]

for i in range(len(X)):
    Y[i] = func3(X[i])

import matplotlib.pyplot as plt
plt.figure()
plt.plot(X,Y)
plt.savefig("1.png")