import itertools

def rozwiaz( a, b, c ):
	res = []
	unikalne = []
	for i in a:
		if i not in unikalne:
			unikalne.append( i )
	for i in b:
		if i not in unikalne:
			unikalne.append( i )
	for i in c:
		if i not in unikalne:
			unikalne.append( i )

	if len( b ) > len( a ):
		a, b = b, a

	a = a[::-1]
	b = b[::-1]
	c = c[::-1]

	for p in itertools.permutations( range( 0, 10 ) ):
		w = {}
		for i in range( 0, len( unikalne ) ):
			w[ unikalne[i] ] = p[i]

		wynik = []

		for i in range( 0, len( b ) ):
			wynik.append( w[ a[i] ] + w[ b[i] ] )
		for i in range( len(b), len(a) ):
			wynik.append( w[ a[i] ] )
		for i in range( 0, len( wynik ) ):
			if wynik[i] > 9:
				wynik[i] -= 10
				if i + 1 < len( wynik ):
					wynik[i + 1] += 1
				else:
					wynik.append( 1 )

		if len( wynik ) == len( c ):
			ok = True
			for i in range( 0, len( c ) ):
				if wynik[i] != w[ c[i] ]:
					ok = False
			if ok:
				res.append( [ (x, w[x]) for x in unikalne ] )
	return res


print rozwiaz( 'KIOTO', 'OSAKA', 'TOKIO' )
