#include <cstdio>
#include <vector>
#include <algorithm>

#define LL long long int

using namespace std;

const int maxn = 505;
const LL INF = 1e18;

LL mac[maxn][maxn];
LL dist[maxn][maxn];
bool blok[maxn];
vector<int> zap;
vector<LL> wyn;

int n;

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%lld", &mac[i][j]);

    for(int i = 1; i <= n; i++)
    {
        int a; scanf("%d", &a);
        zap.push_back( a );
    }

    reverse( zap.begin(), zap.end() );

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            dist[i][j] = mac[i][j];

	for(int i = 1; i <= n; i++)
		blok[i] = true;

    vector<int> graf;
    for(int i = 0; i < zap.size(); i++)
    {
        int x = zap[i];
		blok[x] = false;
        for(int u = 1; u <= n; u++)
        {
			//if( blok[u] ) continue;
            for(int v = 1; v <= n; v++)
            {
				//if( blok[v] ) continue;
                if( dist[u][v] > dist[u][x] + dist[x][v] )
                {
                    dist[u][v] = dist[u][x] + dist[x][v];
                }
            }
        }

		LL w = 0;
		for(int a = 1; a <= n; a++)
			for(int b = 1; b <= n; b++)
				if( !blok[a] && !blok[b] )
					w += dist[ a ][ b ];

        wyn.push_back( w );
    }

    reverse( wyn.begin(), wyn.end() );

    for(int i = 0; i < wyn.size(); i++)
        printf("%lld ", wyn[i]);
}
