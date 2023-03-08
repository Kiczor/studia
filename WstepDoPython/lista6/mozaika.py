from duze_cyfry import daj_cyfre
import turtle
import random

zolw = turtle.Turtle()

screen = turtle.Screen()
screen.colormode( 255 )

W = 20
zajete = {}
k = {}

def kwadrat( bok, kolor ):
	zolw.fill( True )
	zolw.color( kolor )
	zolw.pencolor( ( 0, 0, 0 ) )
	for i in range( 4 ):
		zolw.forward( bok )
		zolw.left( 90 )
	zolw.fill( False )

def wypiszliczbe( liczba, x, y, kolor ):
	#kolor = ( random.randint( 0, 255 ), random.randint( 0, 255 ), random.randint( 0, 255 ) )
	for i in range( 5 ):
		for j in range( 5 ):
			if( daj_cyfre( liczba )[i][j] == '#' ):
				zajete[( x + i * W, y + j * W )] = 1
				k[ ( x + i * W, y + j * W ) ] = kolor;
				print "x + i: ", x + i, "y + j: ", y + j
				kwadrat( W, kolor )
			zolw.penup()
			zolw.forward( W )
			zolw.pendown()
		zolw.penup()
		zolw.right( 90 )
		zolw.forward( W )
		zolw.right( 90 )
		zolw.forward( 5 * W )
		zolw.left( 180 )
		zolw.pendown()

	zolw.penup()
	zolw.forward( 6 * W )
	zolw.left( 90 )
	zolw.forward( 5 * W )
	zolw.right( 90 )
	zolw.pendown()

def mozna( liczba, x, y ):
	for i in range( 5 ):
		for j in range( 5 ):
			if( daj_cyfre( liczba )[i][j] == '#' and ( ( (x + i * W, y + j * W ) in zajete ) or ( (x + (i - 1) * W, y + j * W ) in k ) or ( (x + i * W, y + (j - 1) * W ) in k ) or ( (x + (i + 1) * W, y + j * W ) in k) or ( (x + i * W, y + (j + 1) * W ) in k ) ) ):
				return False
	return True

zolw.penup()
zolw.setposition( -400, 0 )
zolw.pendown()

zolw.speed(0)

R = 450
licz = 40

listakolorow = []
for i in range( 10 ):
	listakolorow.append( (random.randint( 0, 255 ), random.randint( 0, 255 ), random.randint( 0, 255 ) ) )

while( licz > 0 ):
	zolw.penup()
	tx = random.randrange( -R, R, W )
	ty = random.randrange( -R, R, W )
	zolw.setposition( tx, ty )
	zolw.pendown()

	rkolor = random.choice( listakolorow )

	d = random.randrange( 0, 9 )
	if( mozna( d, tx, ty ) ):
		wypiszliczbe( d, tx, ty, rkolor )
		licz -= 1

	print zajete
