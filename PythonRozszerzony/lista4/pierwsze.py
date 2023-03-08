import math
import time

def pierwsze_imperatywne( n ):
	w = []
	pierwsze = range( 2, n + 1 )
	for i in pierwsze:
		x = i + i
		while x < n + 1:
			if x in pierwsze:
				pierwsze.remove( x )
			x += i
	return pierwsze

def pierwsze_funkcyjne( n ):
	l = range( 2, n + 1 )
	w = filter( lambda x: len( filter( lambda y: x % y == 0 , range( 2, int( math.sqrt(x) ) + 1 ) ) ) == 0, l )
	return w

def pierwsze_skladana( n ):
	l = range( 2, n + 1 )
	zl = [ x for x in l for y in range( 2, int( math.sqrt(x) ) + 1 ) if x % y == 0 ]
	return [ x for x in l if x not in zl ]

print pierwsze_imperatywne( 100 )
print pierwsze_funkcyjne( 100 )
print pierwsze_skladana( 100 )

t = time.time()
pierwsze_imperatywne( 100 )
t2 = time.time()
print t2 - t

t = time.time()
pierwsze_funkcyjne( 100 )
t2 = time.time()
print t2 - t

t = time.time()
pierwsze_skladana( 100 )
t2 = time.time()
print t2 - t
