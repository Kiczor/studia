#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 1005;

int s[maxn];

int n, m, srodek;

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++)
    {
        int a, b; scanf("%d%d", &a, &b);

        s[a] ++;
        s[b] ++;
    }

    for(int i = 1; i <= n; i++)
    {
        if( s[i] == 0 )
            srodek = i;
    }

    printf("%d\n", n - 1 );
    for(int i = 1; i <= n; i++)
        if( i != srodek )
            printf("%d %d\n", srodek, i);
}
