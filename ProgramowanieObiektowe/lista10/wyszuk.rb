class Kolekcja
	def initialize
		@t = []
	end

	def get( i )
		if @t[i] == nil
			print "nie mozna sie odwolac do niezadeklarowanego elementu\n"
			return
		end
		@t[i]
	end

	def length
		@t.length
	end

	def set( i, x )
		@t[i] = x
	end

	def next( i )
		while @t[i] == nil and i < @t.length
			i += 1
		end
		i
	end

	def swap( i, j )
		if @t[i] == nil or @t[j] == nil
			print "nie mozna zamieniac niezadeklarowanego elementu\n"
			return
		end
		tmp = @t[i]
		@t[i] = @t[j]
		@t[j] = tmp
	end

	def wypisz
		i = 0
		while i < @t.length
			print @t[i], " "
			i += 1
		end
		print ", len:", @t.length, "\n"
	end
end

class Wyszukiwanie
	def szuk1( kol, x )
		i = 0
		w = -1
		while i < kol.length
			if kol.get( i ) == x
				w = i
			end
			i += 1
		end
		w
	end

	def szuk2( kol, x )
		pocz = 0
		konc = kol.length
		sr = ( pocz + konc ) / 2
		while pocz < konc
			#print "sr: ", sr, "\n"
			if kol.get( sr ) < x
				pocz = sr + 1
			else
			 	konc = sr
			end

			sr = ( pocz + konc ) / 2
		end


		if kol.get( sr ) == x
			sr
		else
			-1
		end
	end
end

t = Kolekcja.new
t.set( 0, 2 )
t.set( 1, 3 )
t.set( 2, 5 )
t.set( 3, 7 )

s = Wyszukiwanie.new
print s.szuk1( t, 3 ), "\n"
print s.szuk2( t, 5 )
