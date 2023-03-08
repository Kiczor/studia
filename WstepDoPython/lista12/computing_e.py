from math import factorial

# exp(1) value from Wikipedia
# 2.71828182845904523536028747135266249775724709369995
# 2.71828182845904523536028747135266249775724709369870

# Potrzebne: add, mul, truediv

def nwd( a, b ):
    if b == 0:
        return a
    return nwd( b, a % b )

class R:
    def __init__(self, n, d=1):
        self.n = n
        self.d = d

    def skroc( self ):
        w = nwd( self.n, self.d )
        return R( self.n / w, self.d / w )

    def __mul__(self, y):
        x = self
        return skroc( R(x.n * y.n, x.d * y.d) )

    def __add__(self, y):
        x = self
        return skroc( R(x.n * y.d + y.n * x.d , x.d * y.d) )

    def __sub__(self, y):
        x = self
        return R( x.n * y.d - y.n * x.d, x.d * y.d )

    def __mul__(self, y):
        x = self
        return R( x.n * y.n, x.d * y.d )

    def __div__(self, y):
        x = self
        return R( x.n * y.d, x.d * y.n )

    def __str__(self):
        return '%d/%d' % (self.n, self.d)

    def inv(self):
        return R(self.d, self.n)

    def __truediv__(self, y):
        return self * y.inv()

    def digits(self, N):
        value = 10 ** N * self.n // self.d
        res = str(value)
        return res[0] + '.' + res[1:]  # niepoprawne, jeżel liczba >= 10


x = R(1,2)
y = R(1,3)

s = R(0)

for i in range(440):
    s = s + R(1, factorial(i))

print (s.digits(40))
#print (s)


#print (x + y + x)
