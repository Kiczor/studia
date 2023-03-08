def zaszyfruj( tekst, klucz ):
	wyn = ""
	for i in tekst:
		wyn += chr( ord( i ) ^ klucz )
	return wyn

def odszyfruj( tekst, klucz ):
	return zaszyfruj( tekst, klucz )

print zaszyfruj( "python", 7 )
print odszyfruj( zaszyfruj( "python", 7 ), 7 )
