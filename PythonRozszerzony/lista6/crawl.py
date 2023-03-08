import requests
from bs4 import BeautifulSoup
import re

#def jestadresem( s ):
#adres = '([a-zA-Z]+\.)*[a-zA-Z]*[a-zA-Z]+'
#automat = re.compile( 'https://' + adres )

def zle( s ):
    if s[-4:] == '.pdf':
        return True
    return False

def crawl( start_page, distance, action, vis = [] ):
    vis.append( start_page )
    s = requests.get( start_page )
    strona = s.content
    wynik = [(start_page, action(start_page))]
    if distance > 0:
        bs = BeautifulSoup( strona, 'html.parser' )
        for link in bs.find_all( 'a' ):
            l = link.get('href')
            if zle( l ):
                continue
            print( l )
            if not l in vis:
                wynik += ( crawl( start_page + l, distance - 1, action ) )
    return wynik

def zdaniazX( page ):
    s = requests.get( page )
    zaw = s.content
    zdanie = '[A-Za-z,;\'\" \d]+Python([A-Za-z,;\'\" \d])*[.?!\n]'
    z = BeautifulSoup( zaw, 'html.parser' )
    automat = re.compile( zdanie )
    return [ pyt.group() for pyt in automat.finditer( z.text ) ]

print( zdaniazX( 'https://en.wikipedia.org/wiki/Python_(programming_language)' ) )
print( crawl( 'https://www.ii.uni.wroc.pl/~marcinm/dyd/python/', 2, zdaniazX ) )
