def vat_faktura( lista ):
	suma = 0
	for e in lista:
		suma += e
	return suma + 0.23 * suma

def vat_paragon( lista ):
	wynik = 0
	for e in lista:
		wynik += e * 1.23
	return wynik

zakupy = [0.2, 0.5, 4.59, 6]
print vat_faktura( zakupy )
print vat_paragon( zakupy )
