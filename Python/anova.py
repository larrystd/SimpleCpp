#!/usr/bin/env python3.7
# -*- encoding: utf-8 -*-
'''
@File    :   anova.py
@Time    :   2021/01/03 17:09:20
@Author  :   Rui Kong 
@Version :   1.0
@Contact :   Venray.Kong@outlook.com
@License :   (C)Copyright 2017-2018, Liugroup-NLPR-CASIA
@Desc    :   None
'''

import numpy as np
from scipy.stats import f

def anova_single(X):
    """ ANOVA of single factor

    Args:
        X (2-d matrix, double[m*n]): [column is level and row is number of expriments]
    """  
    r = X.shape[0]
    n = X.shape[1]
    num = r*n
    X_ = np.mean(X,axis=1)  # axis等于几，就理解成对那一维值进行压缩. 因此只能对一维向量求均值. 输入[0,1]对压缩两维度
    Q_a = np.sum((X_ -  np.mean(X_))**2 *n)
    
    X_m_matrix = np.ones(shape=X.shape)
    for i in range(len(X_)):
        X_m_matrix[i] = X_m_matrix[i]*X_[i]
    Q_e = np.sum((X - X_m_matrix)**2)
    Q_r = np.sum((X - np.mean(X_))**2)
    
    print ("Q_A",Q_a)
    print ("Q_E",Q_e)
    print ("Q_R",Q_r) 
    F = (Q_a/(r-1))/(Q_e/(num-r))

    print ("f_value", F)
    f_test = f.ppf(0.95,dfn=X.shape[0]-1,dfd=np.size(X)-X.shape[0]) # f分布 下侧分位数
    print ("95% confidence test Ftest", f_test)

    if F <= f_test:
        print ("Accept orgin hypothesis")
    else:
        print ("Refuse orgin hypothesis")

def anova_double(Y):
    """[anova of two factors, repeat experiments >= 2]

    Args:
        Y ([2-d matrix ]): [description]
    """  
    [r,s,l] = Y.shape 
    X_A_mean = np.mean(Y,axis=(1,2))
    X_B_mean = np.mean(Y,axis=(0,2))
    X_I_mean =  np.mean(Y,axis=2)
    X_mean = np.mean(Y)

    Q_A = s*l*np.sum((X_A_mean-X_mean)**2)
    Q_B = r*l*np.sum((X_B_mean-X_mean)**2)

    Q_I = l*np.sum((X_I_mean-np.transpose(np.tile(X_A_mean,(s,1)))-np.tile(X_B_mean,(r,1))+X_mean)**2)
    Q_E = np.sum((Y - np.transpose(np.tile(np.mean(Y,axis=2),(l,1,1)),[1,2,0]))**2)

    print (Q_A)
    print (Q_B)
    print (Q_I)
    print (Q_E)
    df = [r-1,s-1,(r-1)*(s-1), r*s*(l-1)]
    Q_mean_list = [Q_A/df[0],Q_B/df[1],Q_I/df[2], Q_E/df[3]]
    F_A = Q_mean_list[0]/Q_mean_list[-1]
    F_B = Q_mean_list[1]/Q_mean_list[-1]
    F_I = Q_mean_list[2]/Q_mean_list[-1]

    print ("F_A",F_A,"95% F_test", f.ppf(0.95,dfn=df[0],dfd=df[-1]))
    print ("F_B",F_B,"95% F_test", f.ppf(0.95,dfn=df[1],dfd=df[-1]))
    print ("F_I",F_I,"95% F_test", f.ppf(0.95,dfn=df[2],dfd=df[-1]))






if __name__ == "__main__":
    """ test of single factor anova
    """    
    X = [[2,4,3,2,4,7,7,2,5],
    [5,6,8,5,10,7,12,6,6],
    [7,11,6,6,7,9,5,10,6]]
    X = np.array(X)
    anova_single(X)  

    Y = [[[15,15,17],[19,19,16],[16,18,21]],
    [[17,17,17],[15,15,15],[19,22,22]],
    [[15,17,16],[18,17,16],[18,18,18]],
    [[18,20,22],[15,16,17],[17,17,17]]]  # 双因素样本表示的三维矩阵一定要写对
    Y1 = [[[258],[279],[242]],
    [[302],[314],[336]],
    [[321],[318],[327]]]
    Y = np.array(Y)
    anova_double(Y)
"""
np.transpose 交换轴
np.tile 扩展数组， 一般用于矩阵与向量加减， 扩展向量使其计算有理
n
    
    print (Y[3])
    print (Y[:,0])

    X_A_mean = np.mean(Y,axis=(1,2))
    [r,s,l] = Y.shape
    print (s)
    print (np.transpose(np.tile(X_A_mean, (s,1))))

    print (np.tile(np.mean(Y,axis=(2)),(3,1)))


"""
""" 
X = np.array([[1,2,3],[4,5,6]])
print (np.mean(X))
print (np.mean(X,axis=1))   
print ((np.mean(X,axis=1) -  np.mean(X))**2 * X.shape[0])
print (X.shape)


print (X_)
r = np.ones(shape=X.shape)
for i in range(len(X_)):
    r[i] = r[i]*X_[i]
print (r)

# print (X-np.mean(X,axis=1))
"""