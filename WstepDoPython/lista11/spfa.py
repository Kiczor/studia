from turtle import *
import random
import time
import math

M = 300
N = 10

speed('fastest')

points = []
for i in range(N):
	points.append( (random.randint(-M,M), random.randint(-M,M)) )

#jaka jest najlepsza sciezka do punktu
distance = {}
for i in points:
	distance[i] = []

def draw_points(ps):
	pu()
	fillcolor('red')
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

def spfa( point ):
	distance[point] = point
	q = [ point ]
	while len( q ) > 1:
		u = q[o]
		q = q[1::]
		for i in points:
			if i != u and ( distance[i] == [] or distance[i] > length( distance[u] ) + dist( u, i ) ):
				distance[i] = distance[u] + i
				q.append( ( i, distance[i] ))

draw_points(points)

spfa( points[0] )

print distance

draw_line(distance[N - 1], 'black')

input()
