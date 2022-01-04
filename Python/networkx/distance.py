"""
Average distance： 这个很好理解，就是所有两两节点之间的最短距离的平均值，最直接的描述了图的紧密程度。
Eccentricity：这个参数描述的是从任意一个节点，到达其他节点的最大距离
Diameter：图中的最大两个节点间的距离
Radius：图中的最小两个节点间的距离
Periphery： 和 Diameter 对应，那些最大节点距离等于 diameter 的节点
Center： 和 Radius 对应，那些最大节点距离等于 radius 的节点
"""
# Example code using networkx
import networkx as nx

G = nx.Graph()
G.add_edges_from([('A', 'K'), ('A', 'B'), ('A', 'C'), ('B', 'C'),
                  ('B', 'K'), ('C', 'E'), ('C', 'F'), ('D', 'E'),
                  ('E', 'F'), ('E', 'H'), ('F', 'I'), ('I', 'J')])

# ==> Average distance (Average Shortest Path Length)
print(nx.average_shortest_path_length(G))
# 2.3777777777777778

# ==> Diameter
print(nx.diameter(G))
# 5

# ==> Eccentricity
print(nx.eccentricity(G))
# {'K': 5, 'I': 4, 'E': 3, 'D': 4, 'H': 4, 
#  'B': 4, 'A': 4, 'F': 3, 'C': 3, 'J': 5}

# ==> Radius
print(nx.radius(G))
# 3

# ==> Periphery
print(nx.periphery(G))
# ['K', 'J']

# ==> Center
print(nx.center(G))
# ['E', 'F', 'C']

"""
import matplotlib.pyplot as plt #导入科学绘图包
import networkx as nx
G=nx.random_graphs.barabasi_albert_graph(1000,10)#生成n=1000,m=10的无标度的图
print ("某个节点的度:",G.degree(0))#返回某个节点的度
# print("所有节点的度:",G.degree())#返回所有节点的度
# print("所有节点的度分布序列:",nx.degree_histogram(G))#返回图中所有节点的度分布序列（从1至最大度的出现频次）
degree=nx.degree_histogram(G)#返回图中所有节点的度分布序列
x=range(len(degree))#生成X轴序列，从1到最大度
y=[z/float(sum(degree))for z in degree]#将频次转化为频率，利用列表内涵
plt.scatter(x,y,s=1,color=(1,0,0))#在双对坐标轴上绘制度分布曲线
plt.show()#显示图表
"""