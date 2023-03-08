import random

def permutacja( n ):
    L = []
    wybrane = []
    ilosc = 0
    for i in range( n ):
        wybrane += [0]
        
    while( ilosc < n ):
        p = random.randint( 0, n - 1 )
        if( wybrane[p] == 0 ):
            L.append( p )
            wybrane[p] = 1
            ilosc += 1

    return L

for i in range( 5 ):
    print permutacja( 10 )
