import networkx as nx
G = nx.random_graphs.barabasi_albert_graph(1000,3)   #生成一个n=1000，m=3的BA无标度网络

out_degree = nx.degree_centrality(G) #节点中心度
#in_degree = degree_centrality(G) #入度中心度
#out_closeness = nx.closeness_centrality(G.reverse()) #出接近中心度
#in_closeness = nx.closeness_centrality(G) #入接近中心度
#betweenness = nx.betweenness_centrality(G) #中介中心度

print('出度中心度: ', out_degree)
