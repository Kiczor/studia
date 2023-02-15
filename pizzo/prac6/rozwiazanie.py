import json
import sys

filename = input()
automat = {}

with open(filename) as f:
    automat = json.load(f)

alphabet = automat['alphabet']
states = automat['states']
initial = automat['initial']
accepting = automat['accepting']
transitions = automat['transitions']

transfrom = {}
for d in transitions:
    transfrom[(d['from'], d['letter'])] = d['to']

reachable_states = set([initial])
new_states = set([initial])

while len(new_states) > 0:
    tmp = set()
    for q in new_states:
        for c in alphabet:
            tmp = tmp | set([ transfrom[(q, c)] ])
    new_states = tmp - reachable_states
    reachable_states = reachable_states | new_states

states = reachable_states

#print(accepting)

P = [set(accepting), states - set(accepting)]
W = [set(accepting), states - set(accepting)]
#print(f"poczatek P:{P}, W:{W}")
while len(W) > 0:
    A = W[0]
    W = W[1::]
    #print(f"A:{A}")
    for c in alphabet:
        X = set()
        for s in states:
            if transfrom[(s,c)] in A:
                X |= set([s])

        #print(f"X:{X}")

        newP = []
        for Y in P:
            #print(f"Y:{Y}, X n Y:{X & Y}, Y \ X:{Y - X}")
            if len( X & Y ) == 0 or len( Y - X ) == 0:
                newP.append(Y)
                continue
            intyx = X & Y
            difyx = Y - X

            #print(f"Y:{Y}, X n Y:{intyx}, Y \ X:{difyx}")

            #replace Y in P by the two sets X ∩ Y and Y \ X
            newP.append(intyx)
            newP.append(difyx)
            if Y in W:
                #replace Y in W by the two sets X ∩ Y and Y \ X
                for i in range( 0, len(W) ):
                    if W[i] == Y:
                        W[i] = intyx
                        break
                W.append(difyx)
            else:
                if len(intyx) <= len(difyx):
                    W.append(intyx)
                else:
                    W.append(difyx)
        P = newP
    #print(f"P:{P}, W:{W}")

print(len(P))
