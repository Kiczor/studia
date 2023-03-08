def pierwiastek( n ):
	s = 1
	i = 1

	while( s < n ):
		i += 1
		s += 2 * i + 1
	return i

print pierwiastek( 25 )
print pierwiastek( 38 )
