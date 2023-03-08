#include <cstdio>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

const int maxn = 1005;

vector<int> v;
int ile[maxn];

int n;

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n - 1; i++)
    {
        int a, b; scanf("%d%d", &a, &b);

        if( a != n && b != n )
        {
            printf("NO\n");
            return 0;
        }

        if( a != n )
        {
            v.pb( a );
            ile[a] ++;
        }
        if( b != n )
        {
            v.pb( b );
            ile[b] ++;
        }
    }

    sort( v.begin(), v.end() );

    for(int i = 0; i < v.size(); i++)
    {
        if( v[i] < i + 1 )
        {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    int p = 0;
    for(int i = 0; i < v.size(); i++)
    {
        if( v[i] > p )
        {
            if( ile[ v[i] ] == 1 )
            {
                p = v[i];
                printf("%d %d\n", p, n);
                continue;
            }
            p ++;
            printf("%d %d\n", p, n);
            ile[ v[i] ] --;
            while( p < v[i] && ile[ v[i] ] > 0 )
            {
                printf("%d %d\n", p, p + 1);
                ile[ v[i] ] --;
                p++;
            }
        }
    }
}
