#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

#define LL long long int
#define pb push_back
#define mp make_pair
#define st first
#define nd second

using namespace std;

struct prosta
{
    double a, b;
    int numer;

    prosta(){}
};

const int maxn = 100005;
const double eps = 0.0000001;

prosta t[maxn];

double p, k;
int n;

int main()
{
    scanf("%d%lf%lf", &n, &p, &k);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lf%lf", &t[i].a, &t[i].b);
        t[i].numer = i;
    }

    vector<pair<double, int> > v1, v2;
    for(int i = 1; i <= n; i++)
        v1.pb( mp( ( p + eps ) * t[i].a + t[i].b, t[i].numer ) );
    for(int i = 1; i <= n; i++)
        v2.pb( mp( ( k - eps ) * t[i].a + t[i].b, t[i].numer ) );

    sort( v1.begin(), v1.end() );
    sort( v2.begin(), v2.end() );

    /*printf("v1:\n");
    for(int i = 0; i < v1.size(); i++)
        printf("%lf %d\n", v1[i].st, v1[i].nd );
    printf("\nv2:\n");
    for(int i = 0; i < v2.size(); i++)
        printf("%lf %d\n", v2[i].st, v2[i].nd );*/

    for(int i = 0; i < v1.size(); i++)
        if( v1[i].nd != v2[i].nd )
        {
            printf("YES");
            return 0;
        }

    printf("NO");
}
