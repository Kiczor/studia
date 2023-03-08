#include <cstdio>
#include <algorithm>
#include <vector>

#define pb push_back
#define st first
#define nd second
#define mp make_pair

using namespace std;

const int maxn = 200005;

vector<pair<int, int> > G[maxn];
bool vis[maxn];
vector<int> wv;

int n, wynik, root;

int dfs1( int u )
{
    vis[u] = true;
    int x = 0;
    for(int i = 0; i < G[u].size(); i++)
    {
        if( !vis[ G[u][i].st ] )
        {
            if( G[u][i].nd == 0 )
                x += dfs1( G[u][i].st );
            else
                x += dfs1( G[u][i].st ) + 1;
        }
    }

    return x;
}

void dfs2( int u, int res )
{
    vis[u] = true;

    if( res == wynik )
        wv.pb( u );
    if( res < wynik )
    {
        wynik = res;
        wv.clear();
        wv.pb( u );
    }

    for(int i = 0; i < G[u].size(); i++)
    {
        if( !vis[ G[u][i].st ] )
        {
            if( G[u][i].nd == 0 )
                dfs2( G[u][i].st, res + 1 );
            else
                dfs2( G[u][i].st, res - 1 );
        }
    }
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n - 1; i++)
    {
        int a, b; scanf("%d%d", &a, &b);
        G[a].pb( mp( b, 0 ) );
        G[b].pb( mp( a, 1 ) );
    }

    root = dfs1( 1 );

    for(int i = 1; i <= n; i++)
        vis[i] = false;

    wynik = root;
    dfs2( 1, root );

    sort( wv.begin(), wv.end() );

    printf("%d\n", wynik);
    for(int i = 0; i < wv.size(); i++)
        printf("%d ", wv[i] );
}
