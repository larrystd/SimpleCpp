#!/usr/bin/env python3.7
# -*- encoding: utf-8 -*-
'''
@File    :   regression.py
@Time    :   2021/01/07 20:45:13
@Author  :   Rui Kong 
@Version :   1.0
@Contact :   Venray.Kong@outlook.com
@License :   (C)Copyright 2017-2018, Liugroup-NLPR-CASIA
@Desc    :   None
'''

import numpy as np

x = [2,4,5,7,10,12]
y = [3,7,10,15,25,30]

x1 = [0.09, 0.17, 0.19, 0.24, 0.16, 0.22, 0.09, 0.12, 0.09, 0.09,
0.13, 0.16, 0.03, 0.05, 0.13, 0.04, 0.07, 0.04]
y1 = [5.30, 5.55, 5.47, 5.45, 5.07, 5.32, 6.15, 4.70, 5.22, 5.77,
5.12, 5.77, 6.22, 5.82, 5.15, 4.92, 5.20, 5.42]

x2 = [20, 25, 30, 35, 40, 45, 50, 55, 60, 65]
y2 = [13.2, 15.1, 16.4, 17.1, 17.9, 18.7, 19.6, 21.2, 22.5, 24.3]
x = np.array(x2)
y = np.array(y2)
x_mean = np.mean(x)
y_mean = np.mean(y)
temp_1 = np.sum(x*y)
temp_2 = x.shape[0] * x_mean* y_mean 
temp_3 = np.sum(x**2)
temp_4 = x.shape[0]*x_mean**2


b_ = (temp_1-temp_2)/(temp_3-temp_4)
a_ = y_mean - x_mean*b_
print (b_)


l_xy = np.sum((x-x_mean)*(y-y_mean))
l_xx = np.sum((x-x_mean)**2)
l_yy = np.sum((y-y_mean)**2)
r = l_xy/(np.math.sqrt(l_xx*l_yy))
print (r)


X = [[1,2,4],
[1,2.5,6.25],
[1,3,9],
[1,3.5,12.25],
[1,4,16],
[1,5,25],
[1,6,36],
[1,6.5,42.25],
[1,7,49],
[1,7.5,56.25],
[1, 8, 64],
[1,9,81]]
Y = [1.81,1.70,1.65,1.55,1.48,1.40,1.30,1.26,1.24,1.21,1.20,1.18]

X1 = [[1,57,8],
[1,59,10],
[1,49,6],
[1,62,11],
[1,51,8],
[1,50,7],
[1,52,10],
[1,42,6],
[1,61,12],
[1,55,10],
[1, 48, 9],
[1, 57, 9]]
Y1 = [64,71,53,67,55,58,56,51,76,77,57,68]


X = np.array(X1)
Y = np.array(Y1)
temp_ = np.linalg.inv(np.dot(X.T,X))
B_ = np.dot(temp_, X.T)
B_ = np.dot(B_,Y)
print (B_)