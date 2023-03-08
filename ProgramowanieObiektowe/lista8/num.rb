class Fixnum
	def czynniki
		w = []
		d = 1
		while d <= v
			if v % d == 0
				w.push( d )
			end
			d = d + 1
		end
		w
	end
end
