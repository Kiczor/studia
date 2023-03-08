class Formula:
	def __init__( self, left, right ):
		self.left = left
		self.right = right

class Mytrue( Formula ):
	def oblicz( self, zmienne ):
		return True
	def __init__( self ):
		pass
	def __str__( self ):
		return "True"

class Myfalse( Formula ):
	def oblicz( self, zmienne ):
		return False
	def __init__( self ):
		pass
	def __str__( self ):
		return "False"

class And( Formula ):
	def oblicz( self, zmienne ):
		return self.left.oblicz( zmienne ) and self.right.oblicz( zmienne )
	def __str__( self ):
		return str( self.left ) + " and " + str( self.right )

class Or( Formula ):
	def oblicz( self, zmienne ):
		return self.left.oblicz( zmienne ) or self.right.oblicz( zmienne )
	def __str__( self ):
		return str( self.left ) + " V " + str( self.right )

class Impl( Formula ):
	def oblicz( self, zmienne ):
		tl = self.left.oblicz( zmienne )
		tr = self.right.oblicz( zmienne )
		if( tl == True and tr == False ):
			return False
		else:
			return True

	def __str__( self ):
		return str( self.left ) + " => " + str( self.right )

class Eq( Formula ):
	def oblicz( self, zmienne ):
		return self.left.oblicz( zmienne ) == self.right.oblicz( zmienne )

	def __str__( self ):
		return str( self.left ) + " <=> " + str( self.right )

def Not( Formula ):
	def oblicz( self, zmienne ):
		return not self.left.oblicz( zmienne )
	def __init__( self, left ):
		self.left = left
	def __str__( self ):
		return "not " + str( self.left )

class Zmienna( Formula ):
	def __init__( self, s ):
		self.nazwa = s

	def oblicz( self, zmienne ):
		for i in zmienne:
			if self.nazwa == i[0]:
				return i[1]
		print("blad: nie ma zmiennej w slowniku")
		return False

	def __str__( self ):
		return self.nazwa

def znajdz_zmienne( f ):
	if isinstance( f, Zmienna ):
		return [f.nazwa]
	if isinstance( f, Or ) or isinstance( f, And ) or isinstance( f, Eq ) or isinstance( f, Impl ):
		return znajdz_zmienne( f.left ) + znajdz_zmienne( f.right )
	return []

def czytautologia( fr ):
	l = znajdz_zmienne( fr )

	for mask in range( 0, 2 ** len( l ) ):
		wart = []
		for j in range ( 0, len( l ) ):
			if (1 << j) & mask:
				wart.append( [ l[j], True ] )
			else:
				wart.append( [ l[j], False ] )

		if not fr.oblicz( wart ):
			return False

	return True

x = And( Mytrue(), Myfalse() )
print x
print x.oblicz( [] )

y = Impl( Zmienna("x"), And( Zmienna("y"), Mytrue() ) )
print y
print y.oblicz( [ [ "x", True ], [ "y", False ] ] )

print isinstance( x, And )
print znajdz_zmienne( y )
print czytautologia( y )

z = Impl( Myfalse(), y )
print czytautologia( z )

v = Not( z )
print v
print v.oblicz( [ [ "x", True ], [ "y", False ] ] )
