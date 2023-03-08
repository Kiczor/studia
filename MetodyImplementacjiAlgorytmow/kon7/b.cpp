#include <cstdio>
#include <algorithm>
#include <vector>

#define LL long long int

using namespace std;

LL n;

LL nwd( LL a, LL b )
{
	if( b == 0 )
		return a;
	return nwd( b, a % b );
}

LL nww( LL a, LL b )
{
	return a * b / nwd( a, b );
}

int main()
{
	scanf("%lld", &n);

	if( n == 1 )
	{
		printf("1");
		return 0;
	}
	if( n == 2 )
	{
		printf("2");
		return 0;
	}
	if( n == 3 )
	{
		printf("6");
		return 0;
	}

	LL wynik = 0;

	for(LL x = max( 1LL, n - 100 ); x <= n; x++)
		for(LL y = max( 1LL, n - 100 ); y <= n; y++)
			for(LL z = max( 1LL, n - 100); z <= n; z++)
				if( x != z && ( y != z && z != x ) )
					wynik = max( wynik, nww( x, nww( y, z ) ) );


	printf("%lld", wynik);
}
