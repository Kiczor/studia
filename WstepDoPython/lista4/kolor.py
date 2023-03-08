import turtle

zolw = turtle.Turtle()

#zolw.colormode( 255 )

def kwadrat( bok, r, g, b ):
    zolw.fillcolor( (r, g, b) )
    for i in range( 4 ):
        zolw.forward( bok )
        zolw.right( 90 )

kwadrat( 100, 0, 100, 100 )
