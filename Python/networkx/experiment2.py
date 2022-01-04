import networkx as nx

G = nx.read_edgelist('/home/larry/programs/Python/networkx/loc-gowalla_edges.txt', create_using=nx.Graph(), nodetype=int)
#G = nx.read_edgelist('/home/larry/programs/Python/networkx/facebook_combined.txt', create_using=nx.Graph(), nodetype=int)

#G = nx.read_edgelist('/home/larry/programs/Python/networkx/loc-brightkite_edges.txt', create_using=nx.Graph(), nodetype=int)


print(nx.info(G))
connected_component = nx.number_connected_components(G) # 连通块个数

print ("connected_component")
print (connected_component)

print ("diameter")
print (nx.diameter(G))
graphs=list(nx.connected_component_subgraphs(G))
for sub_graph in graphs:
    print(nx.diameter(sub_graph))