import snap
# create a graph TNGraph
G1 = snap.TNGraph.New()
G1.AddNode(1)
G1.AddNode(5)
G1.AddNode(32)
G1.AddEdge(1,5)
G1.AddEdge(5,1)
G1.AddEdge(5,32)

# create a directed random graph on 100 nodes and 1k edges
G2 = snap.GenRndGnm(snap.TNGraph, 100, 1000)
# traverse the nodes
for NI in G2.Nodes():
    print("node id %d with out-degree %d and in-degree %d" % (
        NI.GetId(), NI.GetOutDeg(), NI.GetInDeg()))
# traverse the edges
for EI in G2.Edges():
    print("edge (%d, %d)" % (EI.GetSrcNId(), EI.GetDstNId()))
# traverse the edges by nodes
for NI in G2.Nodes():
    for Id in NI.GetOutEdges():
        print("edge (%d %d)" % (NI.GetId(), Id))

G8 = snap.GenPrefAttach(1000, 3)
# get distribution of connected components (component size, count)
CntV = G8.GetWccSzCnt()
# get degree distribution pairs (degree, count)
CntV = G8.GetOutDegCnt()
# get first eigenvector of graph adjacency matrix
EigV = G8.GetLeadEigVec()
# get diameter of G8
G8.GetBfsFullDiam(100)
# count the number of triads in G8, get the clustering coefficient of G8
G8.GetTriads()
G8.GetClustCf()