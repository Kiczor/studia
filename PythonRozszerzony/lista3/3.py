pam = {}

def sudan( n, x, y ):
	if n == 0:
		return x + y
	if (n, x, y) in pam:
		return pam[ (n, x, y ) ]

	if y == 0:
		return x

	return sudan( n - 1, sudan( n, x, y - 1 ), sudan( n, x, y - 1 ) + y )

print sudan( 1, 7, 8 )
