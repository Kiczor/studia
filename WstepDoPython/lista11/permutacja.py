def transform( s ):
	res = ''
	d = {}

	licz = 0
	for i in s:
		if( i not in d ):
			licz = licz + 1
			d[i] = licz
		res = res + '-' + str( d[ i ] )

	return res[1::]

print transform( 'indianin' )
