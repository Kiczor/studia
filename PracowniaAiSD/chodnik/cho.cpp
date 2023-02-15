#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 200005, maxr = 10005;

int n;
int l[maxn], m[maxn], r[maxn];
int pop[maxn];
bool vis[maxn];
int titer[maxn];
vector<int> pocz[maxr];

int start;
int dfs( int u )
{
    vis[u] = true;
    if( r[u] == 0 )
        return u;

    while( titer[ r[u] ] < (int)pocz[ r[u] ].size() )
    {
        int v = pocz[ r[u] ][ titer[ r[u] ] ];
        titer[ r[u] ]++;
        if( !vis[v] ) 
        {
            pop[v] = u;
            int x = dfs( v );
            if( x != -1 )
                return x;
        }
    }

    return -1;
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &l[i], &m[i], &r[i]);
        pocz[ l[i] ].push_back( i );
    }

    int w = -1, ws = 0;
    for(int i = 0; i < n; i++)
        if( l[i] == 0 )
        {
            start = i;
            int x = dfs( i );
            if( x != -1 )
            {
                w = x;
                ws = start;
                break;
            }
        }
    
    if( w == -1 )
    {
        printf("BRAK");
        return 0;
    }

    vector<int> c;
    int a = w;
    while( a != ws )
    {
        c.push_back( a );
        a = pop[a];
    }
    c.push_back(a);

    reverse( c.begin(), c.end() );
    
    printf("%d\n", (int)c.size() );
    for(int i = 0; i < (int)c.size(); i++)
        printf("%d %d %d\n", l[ c[i] ], m[ c[i] ], r[ c[i] ] );
}
