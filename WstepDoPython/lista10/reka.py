def sumpod( l ):
	s = {0}
	if( len( l ) == 0 ):
		return s
	rs = sumpod( l[1::] )
	for i in rs:
		s.add( i )
		s.add( i + l[0] )
	return s

print sumpod( [1, 2, 3, 100] )
