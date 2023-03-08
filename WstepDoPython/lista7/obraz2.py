import turtle
import random
import time

zolw = turtle.Turtle()

screen = turtle.Screen()
screen.colormode( 255 )

W = 20
wysokosc = 5
szerokosc = 5

jakikolor = {}

def kwadrat( bok, kolor ):
    zolw.fill( True )
    zolw.color( kolor )
    for i in range( 4 ):
        zolw.forward( bok )
        zolw.left( 90 )
    zolw.fill( False )

file = open( "picture.txt", "r" );

def okreslkolory():
    licz = 0
    for line in file:
        v = line.split( " " )
        licz = licz + 1
        szerokosc = len( v )
        for i in range( len( v ) ):
            jakikolor[ ( licz, i ) ] = eval( v[i] )
    wysokosc = licz

def wypiszobrazek2( bok ):
    s = []
    for i in range( wysokosc ):
        for j in range( szerokosc ):
            s.append( ( i, j ) )
    random.shuffle( s )

    print s

    for i in range( len( s ) ):
        x = s[i][0]
        y = s[i][1]
        print x, y

def wypiszobrazek( bok ):
    for line in file:
        v = line.split( " " )
        for i in range( len( v ) ):
            x = eval( v[i] )
            kwadrat( bok, x )
            zolw.penup()
            zolw.forward( bok )
            zolw.pendown()
            print x
        zolw.penup()
        zolw.goto( zolw.pos() + ( - len(v) * bok, - bok ) )
        zolw.pendown()

#zolw.tracer( 0, 0 )
zolw.penup()
zolw.goto( zolw.pos() - ( 300, - 300 ) )
zolw.pendown()

#zolw.speed('fastest')
okreslkolory()
wypiszobrazek2( 5 )
#screen.update()
input()
#time.sleep( 5000 )
