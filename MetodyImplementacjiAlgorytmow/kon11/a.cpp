#include <cstdio>
#include <algorithm>

#define LL long long int

using namespace std;

const int maxn = 200005;

LL t[maxn];

int n;
LL wynik, s;

int main()
{
	scanf("%d%lld", &n, &s);
	for(int i = 0; i < n; i++)
		scanf("%lld", &t[i]);

	sort( t, t + n );

	/*printf("t:\n");
	for(int i = 0; i < n; i++)
		printf("%lld ", t[i]);
	puts("");*/

	if( t[ n / 2 ] == s )
	{
		printf("0");
		return 0;
	}

	if( t[ n / 2 ] < s )
	{
		wynik += s - t[ n / 2 ];
		for(int i = n / 2 + 1; i < n; i++)
			if( s > t[i] )
				wynik += s - t[i];
	}
	else
	{
		wynik += t[ n / 2 ] - s;
		for(int i = 0; i < n / 2; i++)
			if( t[i] > s )
				wynik += t[i] - s;
	}

	printf("%lld", wynik);
}
