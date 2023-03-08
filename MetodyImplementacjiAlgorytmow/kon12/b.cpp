#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 55;

int a[maxn], b[maxn];

int n, m, wynik, st;

int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int j = 0; j < m; j++)
		scanf("%d", &b[j]);

	for(int j = 0; j < m; j++)
		for(int i = 0; i < n; i++)
			if( b[j] % a[i] == 0 )
				st = max( st, b[j] / a[i] );

	for(int j = 0; j < m; j++)
		for(int i = 0; i < n; i++)
			if( b[j] % a[i] == 0 && b[j] / a[i] == st )
				wynik ++;

	printf("%d", wynik);
}
