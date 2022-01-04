def xswap01(l:list):
    temp = l[0]
    l[0] = l[1]
    l[1] = temp


rep = [[1,2,3],[1,2,3]]

xswap01(rep[0])
print ("before rep[0]=rep[1]", id(rep[0][0]), " ", id(rep[1][0]))

print (rep)

rep[0] = rep[1]

print (rep)
print ("after rep[0]=rep[1]", id(rep[0][0]), " ", id(rep[1][0]))

xswap01(rep[0])

print (rep)