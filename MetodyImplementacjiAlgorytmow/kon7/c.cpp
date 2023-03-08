#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int dp[maxn];
int t[maxn];

int n;

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &t[i]);

	int wynik = 0;
	for(int i = 1; i <= n; i++)
	{
		int x = t[i];
		int najw = 0;
		for(int j = 2; j * j <= x; j++)
			if( x % j == 0 )
				najw = max( najw, max( dp[j], dp[x / j] ) );

		for(int j = 1; j * j <= x; j++)
			if( x % j == 0 )
			{
				dp[j] = max( dp[j], najw + 1 );
				dp[x / j] = max( dp[x / j], najw + 1 );
			}

		/*printf("\nx:%d\n", x);
		for(int j = 2; j <= x; j++)
			printf("%d: %d\n", j, dp[j] );*/

		wynik = max( wynik, najw + 1 );
	}

	printf("%d", wynik);
}
