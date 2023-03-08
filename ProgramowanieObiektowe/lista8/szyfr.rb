class Jawna
	def initialize( s )
		@ciag = s
	end
	def zaszyfruj( klucz )
		a = @ciag.split('')
		w = ''
		a.each { |x|
			w += klucz[x]
		}
		wyn = Zaszyfrowana.new( w )
		wyn
	end
	def to_s
		@ciag
	end
end

class Zaszyfrowana
	def initialize( s )
		@ciag = s
	end
	def odszyfruj( klucz )
		w = ''
		a = @ciag.split('')
		a.each { |x|
			klucz.each do |key, value|
				if value == x
					w += key
				end
			end
		}
		wyn = Jawna.new( w )
		wyn
	end
	def to_s
		@ciag
	end
end

klucz1 =
{
	'a' => 'b',
	'b' => 'r',
	'c' => 'd',
	'd' => 'e',
	'e' => 'f',
	'f' => 'g',
	'g' => 'h',
	'h' => 'i',
	'i' => 'j',
	'j' => 'k',
	'k' => 'l',
	'l' => 'm',
	'm' => 'n',
	'n' => 'o',
	'o' => 'p',
	'p' => 'q',
	'q' => 's',
	'r' => 'y',
	's' => 't',
	't' => 'w',
	'u' => 'a',
	'w' => 'v',
	'v' => 'x',
	'x' => 'z',
	'y' => 'u',
	'z' => 'c',
}

x = Jawna.new("gitara")
print x.zaszyfruj(klucz1), "\n"

y = Jawna.new("ruby")
print y.zaszyfruj(klucz1), "\n"

z = Zaszyfrowana.new("yaru")
print z.odszyfruj( klucz1 ), "\n"
