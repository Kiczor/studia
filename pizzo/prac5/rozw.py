import json
import sys

from pysmt.shortcuts import Symbol, Int, GE, LE, Not, And, Plus, Equals, Times, Real, ToReal, get_model
from pysmt.typing import INT

filename = input()
problem = {}

with open(filename) as f:
    problem = json.load(f)

parametry = problem['parametry']
skladniki = problem['składniki']
konflikty = problem['konflikty']
cel = problem['cel']
cel_tyg = problem['cel_tygodniowy']

#print(f"parametry:{parametry}")
#print(f"skladniki:{skladniki}")
#print(f"konflikty:{konflikty}")
#print(f"cel:{cel}")
#print(f"cel_tyg:{cel_tyg}")

skladniklista = [s['nazwa'] for s in skladniki]

wszystkieposilki = [] #warunki na wszystkie posilki
konfexpr = [] #warunki zeby nie bylo konfliktow wykluczajacych sie posilkow
niepuste = [] #posilki niepuste
warunki = [] #warunki do spelnienia: suma dzienna to suma posilkow, suma dni to suma tygodniowa
dziennasuma = []
tygodniowasuma = []
dziedzina = [] #dziedzina wartosci

for day in range(7):
    posilki = [] #typ: [[]]

    posilki.append([Symbol( s['nazwa'] + str(day) + '0', INT ) for s in skladniki]) #ile lacznie kazdego
    for pos in range(1, 6):
        posilki.append([Symbol( s['nazwa'] + str(day) + str(pos), INT ) for s in skladniki])
    #print(posilki)

    tmp = []
    for p in posilki:
        for nz in p:
            tmp.append( GE(nz, Int(0)) )
    dziedzina.append( And(tmp) )

    niepuste.append( And( GE( Plus(posilki[0]), Int(1) ), GE( Plus(posilki[1]), Int(1) ), GE( Plus(posilki[2]), Int(1) ), GE( Plus(posilki[3]), Int(1) ), GE( Plus(posilki[4]), Int(1) ), GE( Plus(posilki[5]), Int(1) ) ) )

    wszystkieposilki.append(posilki)

    for i in range( len( posilki[0] ) ):
        dziennasuma.append( Equals( posilki[0][i], Plus( posilki[1][i], posilki[2][i], posilki[3][i], posilki[4][i], posilki[5][i] ) ) )

tygodniowe = [Symbol( s['nazwa'] + 'T', INT ) for s in skladniki]
dziedzina = And( And(dziedzina), And([GE(x, Int(0)) for x in tygodniowe]) )

for i in range( len(skladniklista) ):
    tmp = []
    for d in range(7):
        tmp.append( wszystkieposilki[d][0][i] )
    tygodniowasuma.append( Equals( tygodniowe[i], Plus( tmp ) ) )

#print(tygodniowasuma)
#print(dziennasuma)
#print(dziedzina)
#print(niepuste)
#print(warunki)

for i in range( len(wszystkieposilki) ):
    for p in parametry:
        psumdzien = []
        for j in range( 1, len(wszystkieposilki[i] ) ):
            for s in range( len( skladniklista ) ):
                #print(f"{wszystkieposilki[i][j][s]}, skladniki[s][p]:{skladniki[s][p]}")
                psumdzien.append( Times( ToReal(wszystkieposilki[i][j][s]), Real(skladniki[s][p]) ) )
        psumdzien = Plus( psumdzien )
        #print(psumdzien)
        warunki.append( And( GE( psumdzien, Real(float(cel[p]["min"])) ), LE( psumdzien, Real(float(cel[p]["max"])) ) ) )

for p in parametry:
    psumtydzien = []
    for s in range( len( skladniklista ) ):
        psumtydzien.append( Times( ToReal(tygodniowe[s]), Real(skladniki[s][p]) ) )
    psumtydzien = Plus( psumtydzien )
    #print(psumtydzien)
    warunki.append( And( GE( psumtydzien, Real(float(cel_tyg[p]["min"])) ), LE( psumtydzien, Real(float(cel_tyg[p]["max"])) ) ) )

#print(warunki)

for k in konflikty:
    #print(k)
    p1 = skladniklista.index( k["nazwa1"] )
    p2 = skladniklista.index( k["nazwa2"] )
    for i in range( len(wszystkieposilki) ):
        for j in range( 1, len( wszystkieposilki[i] ) ):
            #print( wszystkieposilki[i][j] )
            konfexpr.append( Not( And( GE(wszystkieposilki[i][j][p1], Int(1)), GE(wszystkieposilki[i][j][p2], Int(1) ) ) ) )

#print( konfexpr )

#wyrazenie = And( And(konfexpr), And(niepuste), And(warunki), And(dziedzina) )
wyrazenie = And(And(dziedzina), And(niepuste), And(konfexpr), And(tygodniowasuma), And(dziennasuma), And(warunki))
#print(wyrazenie)
rozwiazanie = get_model( wyrazenie )

#print(rozwiazanie)

if rozwiazanie == None:
    print("Nie można wygenerować diety.")
else:
    dnitygodnia = ['poniedziałek', 'wtorek', 'środa', 'czwartek', 'piątek', 'sobota', 'niedziela']
    nazwyposilkow = ['śniadanie', 'lunch', 'obiad', 'podwieczorek', 'kolacja']

    dieta = {}
    for i in range(7):
        dieta[i] = []

    for l in rozwiazanie:
        r = str(l[0])
        ile = int(str(l[1]))
        if r[0] == '\'':
            r = r[1:-1]
        if r[-1] == 'T':
            continue

        nazwa = r[:-2:]
        dzien = int(r[-2])
        posnum = int(r[-1]) - 1
        #print(f"l:{l}, nazwa:{nazwa}, dzien:{dzien}, numer posilku:{posnum}")
        if ile > 0 and posnum >= 0:
            dieta[dzien].append( (nazwa, posnum, ile) )

    for day in range( 7 ):
        print(f"[{dnitygodnia[day]}]")
        posdict = {}
        for i in range(5):
            posdict[i] = []
        for x in dieta[day]:
            posdict[ x[1] ].append((x[0], x[2]))

        #print(posdict)

        for p in range(5):
            wypisz = ""
            for t in posdict[p]:
                wypisz += (t[0] + ', ') * t[1]
            print(nazwyposilkow[p] + ': ' + wypisz[:-2:])

