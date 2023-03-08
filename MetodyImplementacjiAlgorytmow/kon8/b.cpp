#include <cstdio>
#include <vector>
#include <algorithm>

#define LL long long int

using namespace std;

const int maxn = 505;
const LL INF = 1e18;

LL mac[maxn][maxn];
LL dist[maxn][maxn];
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

    LL w = 0;
    vector<int> graf;
    for(int i = 0; i < zap.size(); i++)
    {
        int x = zap[i];
        graf.push_back( x );
        for(int a = 0; a < graf.size(); a++)
        {
            int u = graf[a];
            for(int b = 0; b < graf.size(); b++)
            {
                int v = graf[b];
                if( dist[u][v] > dist[u][x] + dist[x][v] )
                {
                    w -= dist[u][v] - dist[u][x] - dist[x][v];
                    dist[u][v] = dist[u][x] + dist[x][v];
                }
            }
        }

        for(int a = 0; a < graf.size(); a++)
        {
            w += dist[graf[a]][x];
            w += dist[x][graf[a]];
        }

        for(int a = 0; a < graf.size(); a++)
        {
            int u = graf[a];
            for(int b = 0; b < graf.size(); b++)
            {
                int v = graf[b];
                if( dist[v][x] > dist[v][u] + dist[u][x] )
                {
                    w -= dist[v][x] - dist[v][u] - dist[u][x];
                    dist[v][x] = dist[v][u] + dist[u][x];
                }

                if( dist[x][v] > dist[x][u] + dist[u][v] )
                {
                    w -= dist[x][v] - dist[x][u] - dist[u][v];
                    dist[x][v] = dist[x][u] + dist[u][v];
                }
            }
        }

        wyn.push_back( w );
    }

    reverse( wyn.begin(), wyn.end() );

    for(int i = 0; i < wyn.size(); i++)
        printf("%lld ", wyn[i]);
}
