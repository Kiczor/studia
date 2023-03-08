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

	def wykres( left, right, top, down )
		x = left
		y = top
		ls = 200.0
		skokpoz = (right - left) / ls
		skokpio = (top - down) / ls
		i = 0
		j = 0

		print "NOWY WYKRES\n"
		print "skok poziomy: #{skokpio}, skok pionowy: #{skokpoz}\n"

		while i < ls
			while j < ls
				#print "x: #{x}, y: #{y}, -: #{@f.call(x) - y}\n"
				if (@f.call(x) - y < skokpio) and (@f.call(x) - y >= 0.0)
					print "#"
				else
					if y <= 0.0 and y >= -skokpio
						print "-"
					else
						if x <= 0.0 and x >= -skokpoz
							print "|"
						else
							print " "
						end
					end
				end
				j += 1
				x += skokpoz
			end
			print "\n"
			i += 1
			j = 0
			y -= skokpio
			x = left
		end
	end
end

f = Funkcja.new( proc{ |x| x * x } )
g = Funkcja.new( proc{ |x| x * x + 2 * x } )
h = Funkcja.new( proc{ |x| Math.sin(x) } )
a = Funkcja.new( proc{ |x| x * Math.sin(x) } )

f.wykres( -10.0, 10.0, 10.0, -10.0 )
g.wykres( -10.0, 10.0, 10.0, -10.0 )
h.wykres( -10.0, 10.0, 10.0, -10.0 )
a.wykres( -10.0, 10.0, 10.0, -10.0 )
