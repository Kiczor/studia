def kompresja( s ):
	w = ''
	i = 0
	while i < len(s):
		ile = 0
		c = s[i]
		while i + 1 < len(s) and s[i] == s[i + 1]:
			ile += 1
			i += 1
		if( ile > 2 ):
			w += str(ile + 1) + c
		else:
			if ile == 1:
				w += c + c
			else:
				w += c
		i += 1
	return w

def dekompresja( s ):
	w = ''
	i = 0
	while i < len(s):
		liczba = ''
		if 48 < ord( s[i] ) and ord( s[i] ) <= 57:
			liczba = s[i]
			while i + 1 < len(s) and 48 < ord( s[i + 1] ) and ord( s[i + 1] ) <= 57:
				liczba += s[i + 1]
				i += 1

		if liczba != '':
			i += 1
			w += int( liczba ) * s[i]
		else:
			w += s[i]
		i += 1
	return w

print kompresja( 'suuuuuupeeeeeeer' )
print dekompresja( '7a81b' )
print dekompresja( kompresja( 'suuuuuupeeeeeeer' ) )
