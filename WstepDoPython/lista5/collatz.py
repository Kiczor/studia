def F(n):
    if( n == 1 ):
        return 0
    if( n % 2 == 0 ):
        return F( n / 2 ) + 1
    else:
        return F( 3 * n + 1 ) + 1

def analiza_collatza( a, b ):
    suma = 0
    L = []
    minimum = F( a )
    maksimum = 0
    for i in range( a, b ):
        x = F( i )
        minimum = min( minimum, x )
        maksimum = max( maksimum, x )
        suma += x
        L += [x]

    srednia = suma / ( b - a + 1 )
    L.sort()

    mediana = 0
    if( len( L ) % 2 == 1 ):
        mediana = L[ len( l ) / 2 ]
    else:
        mediana = ( L[ len( L ) / 2 - 1 ] + L[ len( L ) / 2 ] ) / 2

    print a, b
    print "srednia energia: ", srednia
    print "mediana: ", mediana
    print "maksimum: ", maksimum
    print "minimum: ", minimum

analiza_collatza( 5, 7 )
