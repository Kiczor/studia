import itertools

def sprawdz( c ):
    pop = 0
    for i in range( 0, len( c ) ):
        if c[i][0] != pop:
            return -1

        if c[i][2] == 0:
            return i
        pop = c[i][2]
    
    return -1

def wszystko( kl ):
    p = []
    for i in range( 0, len( kl ) ):
        p.append( i )

    for perm in itertools.permutations( p ):
        temp = []
        for i in perm:
            temp.append( kl[i] )
        x = sprawdz( temp )
        if x != -1:
            w = []
            for i in range( 0, x + 1 ):
                w.append( temp[i] )
            return w
    return []

wejscie = open( 'test.in' )
n = -1
klocki = []
for line in wejscie:
    if n == -1:
        n = int( line )
        continue

    l = line.split(  )
    klocki.append( ( int(l[0]), int(l[1]), int(l[2]) ) )

wynik = wszystko( klocki )

if wynik == []:
    print( 'BRAK' )
else:
    print( len( wynik ) )
    for i in wynik:
        print( str( i[0] ) + ' ' + str( i[1] ) + ' ' + str( i[2] ) )