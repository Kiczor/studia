p = []
pierwsze = []

mx = 100000

for i in range( 2, mx + 5 ):
    p.append( 1 )

for i in range( 2, mx ):
    if( p[i] == 1 ):
        x = i + i
        while( x <= mx ):
            p[x] = 0
            x += i

for i in range( 2, mx ):
    if( p[i] == 1 ):
        pierwsze.append( i )

def palindrom( liczba ):
    s = str(liczba)
    pocz = s[0:( ( len(s) + 1 ) / 2 )]
    konc = s[( len(s) / 2 ):len(s)]
    konc = konc[::-1]

    #print " "
    #print "s", s
    #print "pocz:", pocz
    #print "konc", konc

    if( pocz == konc ):
        return True
    else:
        return False

def palindromy( a, b ):
    for i in range( a, b ):
        if( palindrom( i ) and p[i] == 1 ):
            print i

print pierwsze

palindromy( 1, 100000 )
