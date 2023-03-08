def podziel( s ):
    l = []
    t = ""
    for i in range( 0, len( s ) ):
        if( s[i].isspace() and ( not s[i - 1].isspace() and i > 0 ) ):
            l.append( t )
            t = ""
        else:
            if not s[i].isspace():
                t += s[i]
    l.append( t )
    return l

print podziel( "Ania   ma   kota")
