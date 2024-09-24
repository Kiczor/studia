import numpy as np
import random

def restrictdomain(P, beg, end):
    newP = P.copy()
    for i in range(P.shape[0]):
        newP[i] = np.clip( P[i], beg, end )
    return newP

A = 2 * np.random.randn( 5, 5 )
print(A)
A = restrictdomain(A, -1, 1)
print(A)

def g10constraint1(v):
    res = (-1 + 0.0025(v[4] + v[6])) <= 0
    return res

print( g10constraint1( [1, 2, 4, 5, 6, 7, 8, 9] ) )