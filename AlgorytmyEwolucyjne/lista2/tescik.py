import numpy as np
import itertools

def ispermutation( p ):
    for i in range(p.shape[0]):
        if i not in p:
            print("sraka", i)
            return False
    return True

def PMX(ind1, ind2):
    s = ind1.shape[0]
    o1 = np.zeros(s, dtype=np.int32)
    o2 = np.zeros(s, dtype=np.int32)
    beg = np.random.randint(s - 1)
    end = np.random.randint(beg + 1, s)

    o1[beg:end] = ind2[beg:end]
    o2[beg:end] = ind1[beg:end]

    pairing = {}
    for i in range(beg, end):
        pairing[o1[i]] = o2[i]
        pairing[o2[i]] = o1[i]
    
    for i in range(0, beg):
        x = ind1[i]
        if x in o2[beg:end]:
            o2[i] = pairing[x]
        else:
            o2[i] = x

        y = ind2[i]
        if y in o1[beg:end]:
            o1[i] = pairing[y]
        else:
            o1[i] = y

    for i in range(end, s):
        x = ind1[i]
        if x in o2[beg:end]:
            o2[i] = pairing[x]
        else:
            o2[i] = x

        y = ind2[i]
        if y in o1[beg:end]:
            o1[i] = pairing[y]
        else:
            o1[i] = y

    if not ispermutation(o1) or not ispermutation(o2):
        print( "beg, end:\n", beg, end )
        print( "ind1, ind2:\n", ind1, ind2 )
        print( "ind1[b:e], ind2[b:e]:\n", ind1[beg:end], ind2[beg:end] )
        print( "o1, o2:\n", o1, o2 )
        print( "o1[b:e], o2[b:e]:\n", o1[beg:end], o2[beg:end] )
        return 'dupa'

    return o1, o2

#print( PMX(np.random.permutation(10), np.random.permutation(10) ) )

def ox(p1, p2):
    s = p1.shape[0]
    o1 = np.zeros(s, dtype=np.int32)
    o2 = np.zeros(s, dtype=np.int32)
    beg = np.random.randint(s - 1)
    end = np.random.randint(beg + 1, s)

    beg = 3
    end = 7

    o1[beg:end] = p1[beg:end]
    o2[beg:end] = p2[beg:end]

    l1 = []
    l2 = []
    for i in range(end, s):
        if p2[i] not in o1[beg:end]:
            l1.append(p2[i])
        if p1[i] not in o2[beg:end]:
            l2.append(p1[i])

    for i in range(0, end):
        if p2[i] not in o1[beg:end]:
            l1.append(p2[i])
        if p1[i] not in o2[beg:end]:
            l2.append(p1[i])

    print( "l1: ", l1, "\nl2: ", l2)

    for i in range(end, s):
        o1[i] = l1[i - end]
        o2[i] = l2[i - end]
    for i in range(0, beg):
        o1[i] = l1[i + (s - end)]
        o2[i] = l2[i + (s - end)]

    print( "o1: ", o1, "\no2: ", o2 )
    return o1, o2

#ox( np.array( [1,2,3,4,5,6,7,8,9] ), np.array( [4,5,2,1,8,7,6,9,3] ) )

def permutations_diff_on_k(p, n, k):
    res = []
    for kc in itertools.combinations(range(n), k):
        for kcp in itertools.permutations(kc):
            print(kcp)
            tmp = p.copy()
            for i in range(k):
                tmp[kcp[i]] = p[kcp[(i + 1) % k]]
            res.append(tmp)

    return res

print(permutations_diff_on_k(list(range(10)), 10, 3))