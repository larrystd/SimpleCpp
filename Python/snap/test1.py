from __future__ import division

import snap
import math

G=snap.LoadEdgeList(snap.PUNGraph,'predict_delete.txt',0,1)
d_common={}
d_jaccard={}
d_adamic={}


for N1 in G.Nodes():
    #print node_list
    for N2 in G.Nodes():
        if((int(N1.GetId())<int(N2.GetId()))and not((N1.GetId()==N2.GetId())or (N1.IsNbrNId(N2.GetId())))):
            node_list_all=set([])
            value_adamic=0
            for Id in N1.GetOutEdges():
                #save the neighbors
                node_list_all.add(Id)

            #sage the same neighbors of n1 and n2
            node_list_same=set([])
            for Id in N2.GetOutEdges():

                #save the all neighbors of n1 and n2
                if(Id in node_list_all):
                    node_list_same.add(Id)
                    node_list_n=set([])
                    for N_n in G.GetNI(Id).GetOutEdges():
                        #print N_n
                        node_list_n.add(N_n)

                    if(len(node_list_n)>0):
                        value_adamic=value_adamic+1/(math.log(len(node_list_n)))
                    else:
                        value_adamic=value_adamic+1

                node_list_all.add(Id)
            #if (len(node_list_same)>0):
                #print node_list_all,node_list_same      
            key=str(N1.GetId())+'-'+str(N2.GetId())
            value_common=len(node_list_same)
            value_jaccard=len(node_list_same)/len(node_list_all)

            d_common[key]=int(value_common)
            d_jaccard[key]=int(value_jaccard)
            d_adamic[key]=int(value_adamic)

s_common=sorted(d_common.items(),key=lambda item:item[1],reverse=True)
s_jaccard=sorted(d_jaccard.items(),key=lambda item:item[1],reverse=True)
s_adamic=sorted(d_adamic.items(),key=lambda item:item[1],reverse=True)


sample=set([])
with open ('predict_d.txt','r') as f:
    for line in f.readlines():
        data=line.strip().split()
        ids=str(data[0])+'-'+str(data[1])
        sample.add(ids)
count_common=0
count_jaccard=0
count_adamic=0
num=500
#common neighbors
with open ('predict_common.txt','w') as f:
    for i in range(0,num):
        f.write(str(s_common[i][0])+'\n')
        if(str(s_common[i][0]) in sample):
            count_common=count_common+1
    precise=count_common/num
    f.write('precise='+str(precise))
#jaccard
with open ('predict_jaccard.txt','w') as f:
    for i in range(0,num):
        f.write(str(s_jaccard[i][0])+'\n')
        if(str(s_jaccard[i][0]) in sample):
            count_jaccard=count_jaccard+1
    precise=count_jaccard/num
    f.write('precise='+str(precise))
#adamic
with open ('predict_adamic.txt','w') as f:
    for i in range(0,num):
        f.write(str(s_adamic[i][0])+'\n')
        if(str(s_adamic[i][0]) in sample):
            count_adamic=count_adamic+1
    precise=count_adamic/num
    f.write('precise='+str(precise))