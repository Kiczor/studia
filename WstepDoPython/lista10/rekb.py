def podzbiory( a, b, n, poz ):
	print a, b, n, poz
	if( a == b or poz == 0 ):
		return [ [], [b] ]

	l = podzbiory( a + 1, b, n, poz )
	d = podzbiory( a + 1, b, n, poz - 1 )
	for i in l:
		if( len( i ) != poz ):
			l.remove( i )

	return l + [ [a] + i for i in d if len( i ) + 1 == poz ]

print( podzbiory( 2, 5, 3, 3 ) )
