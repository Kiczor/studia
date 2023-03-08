#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100005;

bool bylo[maxn];
int t[maxn];
int w[maxn];

int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
        scanf("%d", &t[i]);

    for(int i = n; i >= 1; i--)
    {
        w[i] = w[i + 1];
        if( !bylo[ t[i] ] )
            w[i] ++;
        bylo[ t[i] ] = true;
    }

    for(int i = 0; i < m; i++)
    {
        int a; scanf("%d", &a);
        printf("%d\n", w[a]);
    }
}
