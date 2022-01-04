import networkx as nx

G = nx.read_edgelist('/home/larry/programs/Python/networkx/loc-gowalla_edges.txt', create_using=nx.Graph(), nodetype=int)
#G = nx.read_edgelist('/home/larry/programs/Python/networkx/loc-brightkite_edges.txt', create_using=nx.Graph(), nodetype=int)
# nx.write_gml(g, "facebook_combined.gml")

print(nx.info(G))

import matplotlib.pyplot as plt                 #导入科学绘图的matplotlib包
import matplotlib as mpl
plt.switch_backend('agg')
mpl.rcParams['agg.path.chunksize'] = 50000

plt.figure()
plt.clf()
degree =  nx.degree_histogram(G)          #返回图中所有节点的度分布序列
x = range(len(degree))                             #生成x轴序列，从1到最大度
y = [z / float(sum(degree)) for z in degree] 
plt.loglog(x,y,color="blue",linewidth=2)           
plt.title("degree distribute")
plt.xlabel("degree")
plt.ylabel("frequency")
plt.savefig("degree distribute")                                                          #显示图表\

plt.figure()
plt.clf()
central_degree = nx.degree_centrality(G)

# print('中心度: ', central_degree)

x = range(len(central_degree))                             #生成x轴序列，从1到最大度
y = [central_degree[i] for i in range(len(central_degree))] 
plt.loglog(x,y,color="blue",linewidth=2)           #在双对数坐标轴上绘制度分布曲线 
plt.title("node central degree")
plt.xlabel("node")
plt.ylabel("central degree")
plt.savefig("central_degree")  


plt.figure()
plt.clf()
cluster_degree = nx.clustering(G)

x = range(len(cluster_degree))                             #生成x轴序列，从1到最大度
y = [cluster_degree[i] for i in range(len(cluster_degree))] 
plt.loglog(x,y,color="blue",linewidth=2)           #在双对数坐标轴上绘制度分布曲线 
plt.title("node cluster")
plt.xlabel("node")
plt.ylabel("cluster")
plt.savefig("cluster_distribute")  




