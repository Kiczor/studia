#include <cstdio>
#include <algorithm>

#define LL long long int

using namespace std;

LL r, l, wynik;

int main()
{
	scanf("%lld%lld", &l, &r);

	for(LL p = 0LL; p <= 62LL; p++)
	{
		if( ( ( 1LL << p ) & l ) != ( ( 1LL << p ) & r ) )
		 	wynik += ( 1LL << p );
		else if( r - l >= ( 1LL << p ) )
			wynik += ( 1LL << p );
	}

	printf("%lld", wynik);
}
