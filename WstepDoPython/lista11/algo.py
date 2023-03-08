from turtle import *
import random
import time
import math

M = 300
N = 100

speed('fastest')

points = []
#for i in range(N):
#    points.append( (random.randint(-M,M), random.randint(-M,M)) )

file = open("punkty.txt", 'r')
for line in file:
    temp = line.split()
    points.append( ( int( temp[0] ), int( temp[1] ) ) )

def draw_points(ps):
    pu()
    fillcolor('yellow')
    for p in ps:
        begin_fill()
        goto(*p)
        circle(10)
        end_fill()
    pd()

def draw_line(ps, c):
    pu()
    goto(*ps[0])
    pd()
    pencolor(c)
    for p in ps[1:]:
        goto(*p)  # == goto(p[0], p[1])

def dist(p1,p2):
    return ((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2) ** 0.5

def length(path):
    d = 0.0
    for i in range(1, len(path)):
        d += dist(path[i-1], path[i])
    return d

best_perm = []
LIM = 30000
obroty = 0

def rek( u, d, p ):
    global LIM, obroty
    obroty += 1
    if( obroty > LIM ):
        return

    if d >= length( best_perm ) and len( best_perm ) != 0:
        return
    if len( p ) == N:
        if( d < length( best_perm ) or len( best_perm ) == 0 ):
            global best_perm
            best_perm = p

    l = []
    for v in points:
        if v not in p:
            l.append( ( dist( u, v ), v ) )

    l.sort()

    if( len( l ) > 0 ):
        rek( l[0][1], d + dist( u, l[0][1] ), p + [ l[0][1] ] )
    if( len( l ) > 1 and random.randint( 1, 10 ) == 1 ):
        rek( l[1][1], d + dist( u, l[1][1] ), p + [ l[1][1] ] )
    if( len( l ) > 2 and random.randint( 1, 30 ) == 1 ):
        rek( l[2][1], d + dist( u, l[2][1] ), p + [ l[2][1] ] )

    return

draw_points(points)

for i in range( 1, N ):
    obroty = 0
    rek( points[i], 0, [ points[i] ] )
    print length( best_perm )
    print obroty

print best_perm
print length( best_perm )

draw_line(best_perm, 'black')

input()
