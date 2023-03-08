#-*- coding: utf-8 -*-

slowa = open( "slowa.txt" )

def litery( s ):
    d = {}
    for c in s:
        if not c in d:
            d[ c ] = 0
        d[ c ] = d[ c ] + 1
    return d;

def czyukladalne( x, y ):
	xl = litery( x )
	yl = litery( y )
	rs = True

	for key, val in xl.iteritems():
		if not key in yl:
			rs = False
		elif xl[key] > yl[key]:
			rs = False

	return rs

def zamien( s1, s2 ):
	nazwisko = s1.lower() + s2.lower()
	l = []
	slo = {}

	for line in slowa:
		sl = line.strip()
		if czyukladalne( sl, nazwisko ):
			print line
			l.append( sl )
			posortowany = ''.join( sorted( sl ) )
			if not posortowany in slo:
				slo[ posortowany ] = [sl]
			slo[ posortowany ].append( sl )

	print l

	for i in range( len( l ) ):
		for j in range( i, len( l ) ):
			dwa = l[i] + l[j]

			nl = litery( nazwisko )
			sl = litery( dwa )

			szukany = ''
			zle = False
			for key, val in nl.iteritems():
				if not key in sl:
					szukany += val * key
				elif val > sl[key]:
					szukany += (val - sl[key]) * key
				elif val < sl[key]:
					zle = True

			szukany = ''.join( sorted( szukany ) )
			if szukany in slo and not zle:
				for k in slo[ szukany ]:
					print l[i], l[j], k
print slowa

zamien( 'Jan', 'Nowak' )
