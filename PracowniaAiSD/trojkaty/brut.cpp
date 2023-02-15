#include <cstdio>
#include <algorithm>
#include <vector>

#define LL long long int

using namespace std;

pair<LL, LL> t[50000];

int n;

LL odl( pair<LL, LL> a, pair<LL, LL> b )
{
	return ( a.first - b.first ) * ( a.first - b.first ) + ( a.second - b.second ) * ( a.second - b.second );
}

LL obwod( pair<LL, LL> a, pair<LL, LL> b, pair<LL, LL> c )
{
	return odl( a, b ) + odl( b, c ) + odl( c, a );
}

int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%lld%lld", &t[i].first, &t[i].second);
	
	pair<LL, LL> A = t[0], B = t[1], C = t[2];
	for(int i = 0; i < n; i++)
		for(int j = i + 1; j < n; j++)
			for(int k = j + 1; k < n; k++)
				if( obwod( A, B, C ) > obwod( t[i], t[j], t[k] ) )
				{
					A = t[i];
					B = t[j];
					C = t[k];
				}
	printf("%lld\n", obwod( A, B, C ) );
	printf("%lld %lld\n%lld %lld\n%lld %lld\n", A.first, A.second, B.first, B.second, C.first, C.second);
}
