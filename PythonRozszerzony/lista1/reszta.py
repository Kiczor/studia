def wydaj( x ):
	mon = [20, 10, 5, 2, 1]
	wyn = []
	for m in mon:
		ile = 0
		while x >= m:
			ile += 1
			x -= m
		if ile > 0:
			wyn.append( ( m, ile ) )
	return wyn

print wydaj( 123 )
