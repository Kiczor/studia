#include <cstdio>
#include <algorithm>
#include <vector>

#define pb push_back
#define LL long long int

using namespace std;

const int maxn = 100005;

vector<int> G[maxn];
bool vis[maxn];

int p, np, n;

void dfs( int u, int lev )
{
    vis[u] = true;

    if( lev % 2 == 0 ) p ++;
    else np ++;

    for(int i = 0; i < G[u].size(); i++)
    {
        if( !vis[ G[u][i] ] )
            dfs( G[u][i], lev + 1 );
    }
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n - 1; i++)
    {
        int a, b; scanf("%d%d", &a, &b);
        G[a].pb( b );
        G[b].pb( a );
    }

    dfs( 1, 0 );

    printf("%lld", (LL)np * (LL)p - (LL)n + 1 );
}
