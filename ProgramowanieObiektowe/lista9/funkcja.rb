class Funkcja
	def initialize( p )
		@f = p
	end

	def value( x )
		@f.call( x )
	end

	def zerowe( a, b, e )
		it = a
		w = nil
		while it + e < b
			if self.value( it ).abs() < e
				w = it
			end
			it += e
		end
		w
	end

	def pole( a, b )
		n = 100000.0
		d = (b - a) / n
		res = 0.0
		i = 1.0
		s = 0.0

		while i <= n
			x = a + i * d
			s = s + @f.call( x - d / 2.0 )
			if i < n
				res = res + @f.call( x )
			end
			i += 1.0
		end
		res = ( d / 6.0 ) * ( @f.call( a ) + @f.call( b ) + 2.0 * res + 4.0 * s )
		res
	end

	def poch( x )
		eps = 0.00001
		(@f.call( x + eps ) - @f.call( x )) / eps
	end

	def wypis
		return @f.toString()
	end
end

f = Funkcja.new( proc{ |x| x * x } )
print f.value( 3 ), "\n"
print f.poch( 3 ), "\n"
print f.zerowe( -1, 1, 0.000001 ), "\n"
print f.pole( 0, 1 ), "\n"

g = Funkcja.new( proc{ |x| x * x + 2 * x } )
print g.pole( 0, 1 ), "\n"
print g.wypis(), "\n"
