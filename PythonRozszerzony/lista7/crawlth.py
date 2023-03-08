import requests
from bs4 import BeautifulSoup
import re
import threading

#def jestadresem( s ):
#adres = '([a-zA-Z]+\.)*[a-zA-Z]*[a-zA-Z]+'
#automat = re.compile( 'https://' + adres )

def zle( s ):
    if s[-4:] == '.pdf':
        return True
    return False

vis = []

def crawl( start_page, distance, action ):
    global vis
    vis.append( start_page )
    print( start_page )
    s = requests.get( start_page )
    strona = s.content
    wynik = [(start_page, action(start_page))]
    print(distance)
    if distance > 0:
        bs = BeautifulSoup( strona, 'html.parser' )
        for link in bs.find_all( 'a' ):
            l = link.get('href')
            print( l )

            if zle( l ):
                continue
            #print( vis )
            
            if not l in vis and l[0] == 'h':
                print( 'odwiedzam' )
                wynik += ( crawl( l, distance - 1, action ) )
    return wynik

def zdaniazX( page ):
    s = requests.get( page )
    zaw = s.content
    zdanie = '[A-Za-z,;\'\" \d]+Python([A-Za-z,;\'\" \d])*[.?!\n]'
    z = BeautifulSoup( zaw, 'html.parser' )
    automat = re.compile( zdanie )
    return [ pyt.group() for pyt in automat.finditer( z.text ) ]

print( zdaniazX( 'https://en.wikipedia.org/wiki/Python_(programming_language)' ) )
print( crawl( 'https://www.ii.uni.wroc.pl/~marcinm/dyd/python/', 1, zdaniazX ) )
#print( crawl( 'https://en.wikipedia.org/wiki/Python_(programming_language)', 1, zdaniazX ))
