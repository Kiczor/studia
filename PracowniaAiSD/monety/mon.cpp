#include <cstdio>
#include <vector>
#include <algorithm>

#define LL long long int

using namespace std;

const int maxf = 1000005;
const int maxn = 105;
const LL INF = 1e18;

LL waga[maxn], nom[maxn];
LL dpmax[maxf], dpmin[maxf];
pair<int, int> popmax[maxf], popmin[maxf];
int ilemax[maxn], ilemin[maxn];

int n, f;

int main()
{
    scanf("%d%d", &f, &n);
    for(int i = 0; i < n; i++)
        scanf("%lld%lld", &nom[i], &waga[i]);
    
    for(int i = 1; i <= f; i++)
    {
        dpmax[i] = -INF;
        dpmin[i] = INF;
    }

    for(int w = 1; w <= f; w++)
    {
    	for(int i = 0; i < n; i++)
        {
		    if( w - waga[i] < 0 ) continue;
            if( dpmax[ w - waga[i] ] + nom[i] > dpmax[w] )
            {
                dpmax[w] = dpmax[ w - waga[i] ] + nom[i];
                popmax[w] = make_pair( w - waga[i], i );
            }
	    	if( dpmin[ w - waga[i] ] + nom[i] < dpmin[w] )
            {
                dpmin[w] = dpmin[ w - waga[i] ] + nom[i];
                popmin[w] = make_pair( w - waga[i], i );
            }
	    }
    }

    //for(int i = 0; i <= f; i++)
    //    printf("%d: dpmax:%lld, gdziepop:%d, jakicofajacy:%d\n", i, dpmax[i], popmax[i].first, popmax[i].second);

    int pmx = f;
    while( pmx != 0 )
    {
        ilemax[ popmax[pmx].second ] ++;
        pmx = popmax[pmx].first;
    }

    int pmn = f;
    while( pmn != 0 )
    {
        ilemin[ popmin[pmn].second ] ++;
        pmn = popmin[pmn].first;
    }

    if( dpmin[f] == INF )
    {
        printf("NIE\n");
        return 0;
    }

    printf("TAK\n");
    printf("%lld\n", dpmin[f]);
    for(int i = 0; i < n; i++)
        printf("%d ", ilemin[i] );
    printf("\n%lld\n", dpmax[f]);
    for(int i = 0; i < n; i++)
        printf("%d ", ilemax[i] );
    printf("\n");
}
