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
    Q_T = np.sum((X - np.mean(X_))**2)
    
    print ("Q_A",Q_a, "Q_A_mean", Q_a/(r-1), "df",r-1)
    print ("Q_E",Q_e, "Q_E_mean", Q_e/(num-r), "df",num-r)
    print ("Q_T",Q_T, "Q_T_mean", Q_T/(num-1), "df",num-1) 
    F = (Q_a/(r-1))/(Q_e/(num-r))

    print ("f_value", F)
    f_test = f.ppf(0.95,dfn=r-1,dfd=num-r) # f分布 下侧分位数
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

def anova_double_one_experiment(Y):
    """[double factor anvoa with one experiment]

    Args:
        Y (2-d matrix[type]): [description]
    """    
    [r,s] = Y.shape
    Y_mean = np.mean(Y)
    Y_mean_r = np.mean(Y,axis=1)
    Y_mean_s = np.mean(Y,axis=0)
    Q_A = s*np.sum((Y_mean_r - Y_mean)**2)
    Q_B = r*np.sum((Y_mean_s - Y_mean)**2)
    Q_E = np.sum((Y - np.transpose(np.tile(Y_mean_r,(s,1))) - np.tile(Y_mean_s,(r,1)) + Y_mean)**2)
    Q = [Q_A,Q_B,Q_E]
    df = [r-1, s-1, (r-1)*(s-1)]
    Q_mean = [Q[i]/df[i] for i in range(len(Q))]
    F_value = [Q_mean[0]/Q_mean[2], Q_mean[1]/Q_mean[2]]
    print ("sum of square", Q)
    print ("degree of freedom", df)
    print ("mean of sum square", Q_mean)
    print ("F-value", F_value)

    print ("95% F_test", f.ppf(0.95,dfn=df[0],dfd=df[2]))
    print ("95% F_test", f.ppf(0.95,dfn=df[1],dfd=df[2]))




if __name__ == "__main__":
    """ test of single factor anova
    """    
    X = [[2,4,3,2,4,7,7,2,5],
    [5,6,8,5,10,7,12,6,6],
    [7,11,6,6,7,9,5,10,6]]

    X1 = [[2.7,4.6,2.6,3.0,3.2,3.8],
    [4.9,4.6,5.0,4.2,3.6,4.2],
    [4.6,3.4,2.9,3.5,4.1,5.1]]

    X2 = [[65,60,69,79,38,68,54,67,68,43],
    [74,71,58,49,58,49,48,68,56,47],
    [22,34,24,21,20,36,36,31,28,33]]

    X3 = [[29.6, 27.3, 28.5, 32.0],
    [27.3, 32.6, 30.8, 34.8],
    [5.8,6.2,11.0,8.3],
    [29.2,32.8,25.0,24.2]]

    X4 = [[2,3,5],
    [8,6,7],
    [7,9,5]]
    X = np.array(X4)
    print ("*"*5,"single fact anova","*"*5)
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


    Z = [[258, 279, 242],
    [302,314,336],
    [321,318,327]]

    Z1 = [[32, 35, 35.5, 38.5],
    [33.5, 36.5, 38, 39.5],
    [36, 37.5, 39.5, 43]]
    Z = np.array(Z1)
    anova_double_one_experiment(Z)


    x = [
    [2,3,5],
    [8,6,7],
    [7,6,5]]
    x = np.array(x)
    C = np.sum(x)**2/(x.shape[0]*x.shape[1])
    ssT = np.sum(x**2)-C
    ssr = np.sum(np.sum(x,axis=0)**2)/3 -C
    sst = np.sum(np.sum(x,axis=1)**2)/3 - C
    sse = ssT-ssr-sst
    print ("ssT",ssT)
    print ("ssr",ssr)
    print ("sst",sst)
    print ("sse",sse)

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