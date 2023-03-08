import numpy as np
import matplotlib.image as mpimg
import matplotlib.pyplot as plt

img = mpimg.imread('gory.png')

def poszarz( l ):
    r = [1,2,3]
    sr = (l[0] + l[1] + l[2]) / 3.0
    r[0] = (sr + l[0]) / 2.0
    r[1] = (sr + l[1]) / 2.0
    r[2] = (sr + l[2]) / 2.0
    return r

for i in range( img.shape[0] ):
    for j in range( img.shape[1] ):
        img[i,j,:3] = poszarz( img[i,j,:3] )

plt.imshow( img )
plt.show()