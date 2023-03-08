#include <cstdio>
#include <algorithm>
#include <cmath>

#define LL long long int

using namespace std;

struct punkt
{
    LL x, y;
};

const int maxn = 100005;

punkt t[maxn];
bool zaj[maxn];

int n;

LL ilowek( punkt a, punkt b, punkt c )
{
    return ( a.x - c.x ) * ( b.y - c.y ) - ( a.y - c.y ) * ( b.x - c.x );
}

bool sprawdz( int A, int B, int poz )
{
    for(int i = 1; i <= n; i++)
        zaj[i] = false;

    bool zle = false;
    int p = 0;
    for(int i = 4; i <= n; i++)
    {
        if( ilowek( t[A], t[B], t[i] ) == 0LL )
            zaj[i] = true;
        else
            p = i;
    }

    /*printf("A:%d, B:%d, p%d, zaj:\n", A, B, p );
    for(int i = 1; i <= n; i++)
        printf("%d ", zaj[i]);
    printf("\n");*/

    for(int i = 4; i <= n; i++)
    {
        if( zaj[i] ) continue;
        if( ilowek( t[poz], t[p], t[i] ) != 0LL )
            return false;
    }
    return true;
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%lld%lld", &t[i].x, &t[i].y);

    if( n <= 3 )
    {
        printf("YES\n");
        return 0;
    }

    if( ilowek( t[1], t[2], t[3] ) == 0 )
    {
        for(int i = 4; i <= n; i++)
        {
            if( ilowek( t[1], t[2], t[i] ) == 0 )
                zaj[i] = true;
        }

        int p1 = 0, p2 = 0;
        for(int i = 4; i <= n; i++)
        {
            if( !zaj[i] && p1 == 0 )
                p1 = i;
            else if( !zaj[i] && p1 != 0 )
                p2 = i;
        }

        bool ok = true;
        for(int i = 4; i <= n; i++)
        {
            if( zaj[i] ) continue;
            if( ilowek( t[p1], t[p2], t[i] ) != 0 )
                ok = false;
        }
        if( ok )
        {
            printf("YES\n");
            return 0;
        }
    }

    if( ( sprawdz( 1, 2, 3 ) || sprawdz( 1, 3, 2 ) ) || sprawdz( 2, 3, 1 ) )
    {
        printf("YES\n");
        return 0;
    }

    printf("NO\n");
}
