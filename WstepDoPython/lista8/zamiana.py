#-*- coding: utf-8 -*-

slownik = open( "pol_ang.txt", "r" );

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
        if xl[key] != yl[key]:
            rs = False
    for key, val in yl.iteritems():
        if xl[key] != yl[key]:
            rs = False
    return rs

def zamien( s1, s2 ):
    nazwisko = s1.lower() + s2.lower()

    x = 0
    for line in slownik:
        x = x + 1
        y = 0
        for line2 in slownik:
            y = y + 1

            if y > x:
                slowo1 = line.split( "=" )[0]
                slowo2 = line2.split( "=" )[0]

                if( czyukladalne( slowo1 + slowo2, nazwisko ) ):
                    print slowo1, slowo2

zamien( 'Czesław', 'Miłosz' )
