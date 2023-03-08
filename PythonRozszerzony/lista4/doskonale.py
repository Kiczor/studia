import time

def doskonale_imperatywne( n ):
	w = []
	for i in range( 1, n ):
		suma = 1
		j = 2
		while j * j <= i:
			if i % j == 0:
				suma += j
				suma += i / j
			j += 1
		if suma == i:
			w.append( i )
	return w

def doskonale_skladana( n ):
	l = range( 1, n )
	return [ x for x in l for j in]

print doskonale_imperatywne( 10000 )
