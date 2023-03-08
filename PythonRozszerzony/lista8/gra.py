import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import random

s = 50
stan = np.zeros( (s,s), dtype = bool )
for i in range( 0, s ):
    for j in range( 0, s ):
        stan[i, j] = random.randint(0, 1)

fig, ax = plt.subplots()
img = ax.imshow(stan)

def update( stan ):
    nstan = np.zeros( (s,s), dtype = bool )
    nstan[:] = stan
    for i in range( 0, s ):
        for j in range( 0, s ):
            zywe = 0
            if i > 0:
                if stan[i - 1, j]:
                    zywe += 1
                if j > 0 and stan[i - 1, j - 1]:
                    zywe += 1
                if j < s - 1 and stan[i - 1, j + 1]:
                    zywe += 1
            if j > 0 and stan[i, j - 1]:
                zywe += 1
            if j < s - 1 and stan[i, j + 1]:
                zywe += 1
            if i < s - 1:
                if stan[i + 1, j]:
                    zywe += 1
                if j > 0 and stan[i + 1, j - 1]:
                    zywe += 1
                if j < s - 1 and stan[i + 1, j + 1]:
                    zywe += 1
            if (zywe < 2 and stan[i, j]) or (zywe > 3 and stan[i, j]):
                nstan[i, j] = False
            if (zywe > 2 and zywe < 4 and stan[i, j]) or (zywe == 3 and not stan[i, j]):
                nstan[i, j] = True
    stan[:] = nstan
    return nstan



def animate( f, img, CurStan, N ):
    nowyStan = np.zeros( (N,N), dtype = bool )
    nowyStan[:] = update(CurStan)
    img.set_data( nowyStan )
    return img,

ani = animation.FuncAnimation(fig, animate, fargs=(img, stan, s), interval=500)
plt.show()
