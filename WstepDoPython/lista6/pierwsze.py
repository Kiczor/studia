czypierwsza = []
lim = 1000000

for i in range( 0, lim ):
    czypierwsza.append( 1 )

for i in range( 2, lim ):
    if( czypierwsza[i] == 1 ):
        j = i
        while( j + i < lim ):
            j += i
            czypierwsza[j] = 0

p = []
for i in range( 2, lim ):
    if( czypierwsza[i] == 1 ):
        p.append(i)

def rozklad( x ):
    l = []
    for d in p:
        while( x % d == 0 ):
            l.append( d )
            x /= d
    return l

print rozklad( 3600 )
