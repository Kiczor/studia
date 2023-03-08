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

print czyukladalne( 'slowo', 'slwoo' )
