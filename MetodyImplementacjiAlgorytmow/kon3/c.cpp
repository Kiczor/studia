#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 200005;

int t[maxn];
int nast[maxn];

int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
        scanf("%d", &t[i]);

    int ost = n + 1;
    for(int i = n; i >= 1; i--)
    {
        nast[i] = ost;
        if( t[i] != t[i - 1] )
        {
            ost = i;
        }
    }

    /*printf("nast:\n");
    for(int i = 1; i <= n; i++)
        printf("%d ", nast[i] );
    printf("\n");*/

    for(int i = 0; i < m; i++)
    {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        if( c != t[a] )
            printf("%d\n", a );
        else
        {
            if( nast[a] <= b )
                printf("%d\n", nast[a] );
            else
                printf("-1\n");
        }
    }
}
