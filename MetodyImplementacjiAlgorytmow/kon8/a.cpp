#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 405;
const int INF = 1e9;

int dist[maxn];
bool g[maxn][maxn];

int n, m;

void bfs( int start, bool pociag )
{
	dist[start] = 0;
	queue<int> q;
	q.push( start );
	while( !q.empty() )
	{
		int u = q.front();
		q.pop();

		for(int v = 1; v <= n; v++)
		{
			if( pociag && !g[u][v] ) continue;
			if( !pociag && g[u][v] ) continue;
			if( dist[u] + 1 < dist[v] )
			{
				dist[v] = dist[u] + 1;
				q.push( v );
			}
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++)
	{
		int a, b; scanf("%d%d", &a, &b);
		g[a][b] = true;
		g[b][a] = true;
	}

	for(int i = 1; i <= n; i++)
		dist[i] = INF;

	if( g[1][n] )
		bfs( 1, false );
	else
		bfs( 1, true );

	if( dist[n] != INF )
		printf("%d", max( dist[n], 1 ) );
	else
		printf("-1");
}
