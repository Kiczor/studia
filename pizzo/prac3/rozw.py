import json
import sys

zainstaluj = {}

zainstaluj = json.load(sys.stdin)

pakiety = zainstaluj["pakiety"]
kolizje = zainstaluj["kolizje"]
wymagania = zainstaluj["wymagania"]
instalowane = zainstaluj["instalowane"]

paktonum = {} # slownik z nazwy pakietu na numer pakietu
for i in range( 0, len( pakiety ) ):
    paktonum[ pakiety[i] ] = i + 1

pakwym = {} # key: nazwa pakietu, val: lista wymaganych pakietow
for d in wymagania:
    pakwym[ d["pakiet"] ] = d["wymaga"]

wynik = []
for p in instalowane:
    tmp = [ -paktonum[p] ]
    for w in pakwym[p]:
        tmp.append( paktonum[w] )
    wynik.append( tmp )

for k in kolizje:
    wynik.append([ -paktonum[ k["pakiet"] ], -paktonum[ k["koliduje_z"] ] ])

for p in instalowane:
    wynik.append([ paktonum[ p ] ])

print(f"p cnf {len(pakiety)} {len(wynik)}")

for l in wynik:
    s = ""
    for x in l:
        s += str(x) + " "
    s += "0"
    print( s )