import turtle
import random
import time

zolw = turtle.Turtle()

screen = turtle.Screen()
screen.colormode( 255 )

W = 20

def kwadrat( bok, kolor ):
    zolw.fill( True )
    zolw.color( kolor )
    for i in range( 4 ):
        zolw.forward( bok )
        zolw.left( 90 )
    zolw.fill( False )

file = open( "picture.txt", "r" );

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

zolw.tracer( 0, 0 )
zolw.penup()
zolw.goto( zolw.pos() - ( 300, - 300 ) )
zolw.pendown()

#zolw.speed('fastest')
wypiszobrazek( 5 )
screen.update()
input()
#time.sleep( 5000 )
