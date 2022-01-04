import networkx as nx
import numpy as np
G = nx.read_edgelist('/home/larry/programs/Python/networkx/loc-gowalla_edges.txt', create_using=nx.Graph(), nodetype=int)
# G = nx.read_edgelist('/home/larry/programs/Python/networkx/loc-brightkite_edges.txt', create_using=nx.Graph(), nodetype=int)
# nx.write_gml(g, "facebook_combined.gml")

print(nx.info(G))

import matplotlib.pyplot as plt                 #导入科学绘图的matplotlib包
import matplotlib as mpl
plt.switch_backend('agg')
mpl.rcParams['agg.path.chunksize'] = 100000

"""
print('*'*20, '度分布曲线', '*'*20)


plt.figure()
plt.clf()
degree =  nx.degree_histogram(G)          # 返回每个度, 对应的节点个数


degree_num = [i*j for i,j in enumerate(degree)]
print ("平均度数", sum(degree_num)/sum(degree))

degree_x = range(len(degree))                             #生成x轴序列，从0到最大度
degree_y = [z/sum(degree) for z in degree]        # 每个度的节点个数， 对总节点的占比

plt.scatter(degree_x,degree_y,marker='.')   

plt.title("degree distribute")
plt.xlabel("degree")
plt.ylabel("frequency")
plt.savefig("degree distribute")                                                          #显示图表\


print('*'*20, '点度中心性', '*'*20)

###中心性

def central_degree(Graph, method=''):

    print ('*'*20, method, '*'*20)
    if method == 'degree_centrality':
        # 这个节点拥有的相邻节点数量
        central_degree = nx.degree_centrality(Graph)
    elif method == 'betweenness_centrality':
        central_degree = nx.betweenness_centrality(Graph)
    plt.figure()
    plt.clf()
    central_degree_x = range(len(central_degree))                          
    central_degree_y = [central_degree[i] for i in central_degree]        # 每个点的重要性
    print ("统计学特征: ")
    print ('度平均中心性', np.mean(central_degree_y))
    print ('度中心性标准差', np.std(central_degree_y))


    plt.scatter(central_degree_x,central_degree_y,marker='.')   
    plt.title("central degree")
    plt.xlabel("vertex")
    plt.ylabel("central degree")
    plt.savefig("central_"+method)  
# 点度中心性越大, 该节点的重要性就越大

central_degree(G, method='degree_centrality')



print('*'*20, '聚类系数', '*'*20)

# 衡量节点聚集的程度

plt.figure()
plt.clf()
cluster_degree = nx.clustering(G)

cluster_degree_x = range(len(cluster_degree)) [-20000:-10000]                              #生成x轴序列，从1到最大度
cluster_degree_y = [cluster_degree[i] for i in cluster_degree] [-20000:-10000]  

# 统计学特征
print ('平均聚类系数', np.mean(cluster_degree_y))
print ('聚类系数标准差', np.std(cluster_degree_y))
plt.scatter(cluster_degree_x,cluster_degree_y,marker='.')   
plt.title("clustering coefficient")
plt.xlabel("vertex")
plt.ylabel("clustering")
plt.savefig("clustering")  

""" 

connected_component = nx.number_connected_components(G) # 连通块个数

print ("connected_component")
print (connected_component)

print ("diameter")
print (nx.diameter(G))

