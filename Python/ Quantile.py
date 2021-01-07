#!/usr/bin/env python3.7
# -*- encoding: utf-8 -*-
'''
@File    :    Quantile.py
@Time    :   2021/01/03 21:12:35
@Author  :   Rui Kong 
@Version :   1.0
@Contact :   Venray.Kong@outlook.com
@License :   (C)Copyright 2017-2018, Liugroup-NLPR-CASIA
@Desc    :   None
'''

import numpy as np


from scipy.stats import norm
from scipy.stats import chi2
from scipy.stats import t
from scipy.stats import f
x_norm = norm.ppf(0.95)  # 标准正态分布，下侧分位数

x_chi = chi2.ppf(0.9,df=4)  # 卡方分布，默认是下侧分位数
x_f = f.ppf(0.95,dfn=2,dfd=18) # f分布 下侧分位数
x_t = t.ppf(0.95,df=4)  # t 分布默认是下侧分位数
print ("norm distribute", x_norm)
print ("chi-square distribute", x_chi)
print ("t distribute", x_t)
print ("f distribute", x_f)
