#-*- coding: utf-8 -*-

file = open( "slowa.txt", "r" );
bylo = {}

for line in file:
    s = line[:len(line) - 2]
    r = "".join( reversed( s ) )
    print s
    print r
    if( r in bylo ):
        print s, r
    bylo[s] = 1
    #print bylo
