def romb( n ):
	for i in range( 0, n + 1 ):
		print (n - i) * ' ' + (2 * i + 1) * '#'
	for i in range( 1, n + 1 ):
		print i * ' ' + (1 + 2 * (n - i)) * '#'

romb( 4 )
