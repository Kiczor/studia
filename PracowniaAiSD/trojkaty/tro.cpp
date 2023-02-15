#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

#define LL long long int

using namespace std;

const int maxn = 500005;
const LL INF = 1e18;

struct punkt
{
	LL x, y;
	punkt(){}
	punkt( LL a, LL b )
	{
		x = a;
		y = b;
	}
};

struct trojkat
{
	punkt A, B, C;
	trojkat(){};
	trojkat( punkt a, punkt b, punkt c ) { A = a; B = b; C = c; }
};

punkt t[maxn];

int n;

LL odl( punkt a, punkt b )
{
	return ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y );
}

LL obwod( trojkat T )
{
	return odl( T.A, T.B ) + odl( T.B, T.C ) + odl( T.C, T.A );
}

LL obwoddobry( trojkat T )
{
	return (LL)( sqrt( (double)odl( T.A, T.B ) ) ) + (LL)( sqrt( (double)odl( T.B, T.C ) ) ) + (LL)( sqrt( (double)odl( T.C, T.A ) ) );
}

void wypisztrojkat( trojkat T )
{
	printf("A: %lld %lld\nB: %lld %lld\nC: %lld %lld\n", T.A.x, T.A.y, T.B.x, T.B.y, T.C.x, T.C.y);
}

trojkat brut( int p, int k )
{
	trojkat res;
	LL obw = INF;
	for(int i = p; i < k; i ++)
		for(int j = i + 1; j < k; j ++)
			for(int l = j + 1; l < k; l ++)
			{
				LL r = obwod( trojkat( t[i], t[j], t[l] ) );
				if( r < obw )
				{
					res = trojkat( t[i], t[j], t[l] );
					obw = r;
				}
			}
	return res;
}

bool cmpX( punkt a, punkt b )
{
	if( a.x == b.x )
		return a.y < b.y;
	return a.x < b.x;
}

bool cmpY( punkt a, punkt b )
{
	if( a.y == b.y )
		return a.x < b.x;
	return a.y < b.y;
}

trojkat solve( int p, int k )
{
	if( k - p < 7 )
		return brut( p, k );

	int s = ( k + p ) / 2;
	LL l = t[s].x;
	trojkat t1 = solve( p, s ), t2 = solve( s, k );
	trojkat dt;
	if( obwod( t1 ) < obwod( t2 ) )
		dt = t1;
	else
		dt = t2;
	LL d = obwod( dt );
	LL sd = obwoddobry( dt ) + 1;
	LL od = sd / 2 + 1;

	//printf("p:%d, k:%d, l:%lld\n", p, k, l);
	//wypisztrojkat( dt );
	//printf("d:%lld, sd:%lld, od:%lld\n", d, sd, od);

	vector<punkt> srodek;
	for(int i = p; i < k; i++)
		if( abs( l - t[i].x ) <= od )
			srodek.push_back( t[i] );
	sort( srodek.begin(), srodek.end(), cmpY );

	/*printf("srodek:\n");
	for(int i = 0; i < (int)srodek.size(); i ++)
		printf("%lld %lld\n", srodek[i].x, srodek[i].y);
	printf("\n");*/

	trojkat wynik = dt; LL wynikobwod = d;
	int ita = 0, itb = 0;
	while( ita < (int)srodek.size() && itb <= (int)srodek.size() )
	{
		while( itb < (int)srodek.size() && abs( srodek[itb].y - srodek[ita].y ) <= od )
			itb ++;
		
		//printf("ita:%d, itb:%d\n", ita, itb);
		for(int i = ita; i < itb; i ++)
			for(int j = i + 1; j < itb; j ++)
				for(int w = j + 1; w < itb; w ++)
				{
					LL temp = obwod( trojkat( srodek[i], srodek[j], srodek[w] ) );
					if( temp < wynikobwod )
					{
						wynikobwod = temp;
						wynik = trojkat( srodek[i], srodek[j], srodek[w] );
					}
				}
		ita ++;
	}

	return wynik;
}

int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%lld%lld", &t[i].x, &t[i].y);
	sort( t, t + n, cmpX );

	/*puts("posortowane");
	for(int i = 0; i < n; i++)
		printf("%lld %lld\n", t[i].x, t[i].y);*/
	
	trojkat wynik = solve( 0, n );
	//printf("%lld\n", obwod( wynik ) );
	printf("%lld %lld\n%lld %lld\n%lld %lld\n", wynik.A.x, wynik.A.y, wynik.B.x, wynik.B.y, wynik.C.x, wynik.C.y);
}
