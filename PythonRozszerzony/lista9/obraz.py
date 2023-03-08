import numpy as np
import matplotlib.image as mpimg
import matplotlib.pyplot as plt

maxroznica = 0.3

img = mpimg.imread('gory.png')

def smutnypiksel( col ):
    if abs( col[0] - col[1] ) < maxroznica and abs( col[1] - col[2] ) < maxroznica and abs( col[2] - col[0] ) < maxroznica:
        return True
    return False

def smooth( x, y, lim1, lim2 ):
    sr = img[x,y,:3]
    for i in range( -lim1, lim2 ):
        for j in range( -lim1, lim2 ):
            if x + i >= 0 and x + i < img.shape[0] and y + j >= 0 and y + j < img.shape[1]:
                tl = img[x+i,y+j,:3]
                sr[0] = ( sr[0] + tl[0] ) / 2.0
                sr[1] = ( sr[1] + tl[1] ) / 2.0
                sr[2] = ( sr[2] + tl[2] ) / 2.0
    return sr

def napraw( x, y ):
    sr = smooth( x, y, 2, 3 )
    #print( sr )
    najw = 0
    kolor = 0
    for i in range( 0, 3 ):
        if sr[i] > najw:
            najw = sr[i]
            kolor = i
    
    for i in range( 0, 3 ):
        if i != kolor:
            sr[i] = sr[i] - 0.03
    
    sr[kolor] = max( sr[kolor] + 0.05, sr[kolor] )
    return sr

for i in range( img.shape[0] ):
    print( i )
    for j in range( img.shape[1] ):
        #print( i, j, img[i, j] )

        if smutnypiksel( img[i,j] ):
            img[i,j,:3] = napraw( i, j )

#wygladzanie
for x in range( img.shape[0] ):
    print( 's', x )
    for y in range( img.shape[1] ):
        img[i,j,:3] = smooth( x, y, 2, 3 )

plt.imshow(img)
plt.show()

