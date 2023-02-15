import numpy as np

file = open("input.in")

res = 0
l = []
allres = []
for line in file:
    if line == "\n":
        res = max( res, np.sum(l) )
        allres.append( np.sum(l) )
        l = []
    else:
        l.append( int(line) )

np.sort(allres)

print(res)
print(allres[-0] + allres[-1] + allres[-2])