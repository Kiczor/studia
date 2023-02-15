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

cstate = initial

trd = {}
for p in transitions:
    trd[(p['from'], p['letter'])] = p['to']

pc = 'a'
while( True ):
    c = sys.stdin.read(1)
    
    #tutaj sprawdzanko eof
    if c == '' or (c == '\n' and pc == '\n'):
        break

    if c == '\n':
        if cstate in accepting:
            print('yes')
        else:
            print('no')
        cstate = initial
    else:
        cstate = trd[ (cstate, c) ]
    pc = c
