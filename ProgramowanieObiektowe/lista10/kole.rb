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

class Sortowanie
	def sort1( k )
		it = 1
		while it < k.length
			i = 0
			while i < it
				if k.get( i ) > k.get( it )
					k.swap( i, it )
				end
				i = k.next( i + 1 )
			end
			it = k.next( it + 1 )
		end
		k
	end

	def mergesort( kol, p, k )
		if k - p == 1
			w = Kolekcja.new
			w.set( 0, kol.get( p ) )
			return w
		end
		sr = ( k + p ) / 2
		left = mergesort( kol, p, sr )
		right = mergesort( kol, sr, k )

		#print "left: "
		#left.wypisz
		#print "right: "
		#right.wypisz

		i = 0
		j = 0
		w = Kolekcja.new
		it = 0
		while i < left.length and j < right.length
			#print "i: ", i, "j: ", j, "\n"
			if left.get( i ) <= right.get( j )
				w.set( it, left.get( i ) )
				i += 1
				it += 1
			else
				w.set( it, right.get( j ) )
				j += 1
				it += 1
			end
		end

		while i < left.length
			w.set( it, left.get( i ) )
			i += 1
			it += 1
		end

		while j < right.length
			w.set( it, right.get( j ) )
			j += 1
			it += 1
		end

		#print "p: ", p, "k: ", k, "w:\n"
		#w.wypisz
		return w
	end

	def sort2( k )
		return mergesort( k, 0, k.length )
	end
end

k = Kolekcja.new
k.set( 0, 10 )
k.set( 1, 1 )
k.set( 2, 5 )
k.set( 3, 3 )

s = Sortowanie.new
k2 = s.sort1( k )
k2.wypisz

t = Kolekcja.new
t.set( 0, 12 )
t.set( 1, 3 )
t.set( 2, 8 )
t.set( 3, 7 )
t.set( 4, 0 )
k3 = s.sort2( t )
k3.wypisz
