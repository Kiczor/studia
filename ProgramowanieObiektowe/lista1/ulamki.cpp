#include <cstdio>

int nwd( int a, int b )
{
	if( b == 0 )
		return a;
	return nwd( b, a % b );
}

struct ulamek
{
	int x, y;

	ulamek(){}
	ulamek( int a, int b ){ x = a; y = b; }

	ulamek *mnoz( ulamek a, ulamek b )
	{
		return new ulamek( a.x * b.x, a.y * b.y );
	}

	ulamek dziel( ulamek a, ulamek b )
	{
		return ulamek( a.x * b.y, a.y * b.x );
	}

	ulamek suma( ulamek a, ulamek b )
	{
		int g = a.x * b.y + b.x * a.y;
		int d = b.y * a.y;
		printf("g:%d, d:%d, nwd:%d\n", g, d, nwd( g, d ) );
		return ulamek( g / nwd( g, d ), d / nwd( g, d ) );
	}

	ulamek roznica( ulamek a, ulamek b )
	{
		return suma( a, ulamek( -b.x, -b.y ) );
	}


};

int main()
{
	ulamek s = ulamek( 3, 4 );
	ulamek t = ulamek( 1, 6 );

	printf("%d/%d\n", s.suma( s, t ).x, s.suma( s, t ).y );
	printf("%d/%d\n", s.mnoz( s, t ) -> x, s.mnoz( s, t ) -> y );
}
