from turtle import *


def kwadrat(bok):
    begin_fill()
    for i in range(4):
        fd(bok)
        rt(90)
    end_fill()

def murek(s,bok):
    for a in s:
        if a == 'f':
            kwadrat(bok)
            fd(bok)
        elif a == 'b':
            kwadrat(bok)
            fd(bok)
        elif a == 'l':
            bk(bok)
            lt(90)
        elif a == 'r':
            rt(90)
            fd(bok)
        elif a == 'R':
            color('black', 'red')
        elif a == 'G':
            color('black', 'green')
        elif a == 'B':
            color('black', 'blue')
        elif a == 'Y':
            color('black', 'yellow')


color('black', 'yellow')

ht()

tracer(0,0) # szybkie rysowanie
#murek('fffffffffrRfffffffffflfffffffffrfffffl',10)
#murek(4 * 'fffffr', 14)
#murek('RfffffrGfffffrBfffffrYfffffr', 20)

s = 'RGBY'
for i in range( 1, 20 ):
    murek( s[ i % 4 ] + 'r' + i * 'f', 20)

update() # uaktualnienie rysunku

input()
