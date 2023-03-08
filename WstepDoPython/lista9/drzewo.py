import turtle

zolw = turtle.Turtle()

M = 10

def drzewo( dl, lev ):
	if( lev > 10 ):
		return

	zolw.forward( dl )

	tpos = zolw.position()
	tkat = zolw.heading()

	zolw.setheading( tkat - 20.0 )
	drzewo( dl - M, lev + 1 )

	zolw.penup()
	zolw.setposition( tpos )
	zolw.setheading( tkat )
	zolw.pendown()

	zolw.setheading( tkat + 20.0 )
	drzewo( dl - M, lev + 1 )

	return

zolw.setheading( 90 )
zolw.penup()
zolw.setposition( 0.0, -450.0 )
zolw.pendown()

drzewo( 150, 1 )
input()
