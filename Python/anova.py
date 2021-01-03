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

def anova_single(X):
    """ ANOVA of single factor

    Args:
        X (double[m*n]): [column is level and row is number of expriments]
    """  
    r = X.shape[0]
    n = X.shape[1]
    num = r*n
    X_ = np.mean(X,axis=1)
    Q_a = np.sum((X_ -  np.mean(X_))**2 *n)
    
    X_m_matrix = np.ones(shape=X.shape)
    for i in range(len(X_)):
        X_m_matrix[i] = X_m_matrix[i]*X_[i]
    Q_e = np.sum((X - X_m_matrix)**2)
    Q_r = np.sum((X - np.mean(X_))**2)

    print (Q_a)
    print (Q_e)
    print (Q_r)

    return Q_a/(r-1), Q_e/(num-r), Q_r/(num-1)  # return mean of Q_A, Q_E, Q_R

def anova_double(X):
    """[anova of two factors]

    Args:
        X ([type]): [description]
    """    

if __name__ == "__main__":
    """ test of single factor anova
    """    
    X = [[2,4,3,2,4,7,7,2,5],
    [5,6,8,5,10,7,12,6,6],
    [7,11,6,6,7,9,5,10,6]]
    X = np.array(X)
    Q_A, Q_E,Q_T = anova_single(X)  
    F = Q_A/Q_E
    print (Q_A)
    print (Q_E)
    print (Q_T)
    print (F)

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