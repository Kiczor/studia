#include <cstdio>
#include <algorithm>
#include <vector>

#define LL long long int
#define st first
#define nd second
#define mp make_pair

using namespace std;

const int maxn = 100005;

LL t[maxn], upt[maxn], upz[maxn];
pair<pair<int, int>, LL> zap[maxn];

int n, m, k;

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; i++)
        scanf("%lld", &t[i]);

    for(int i = 1; i <= m; i++)
        scanf("%d%d%lld", &zap[i].st.st, &zap[i].st.nd, &zap[i].nd);

    for(int i = 1; i <= k; i++)
    {
        int a, b; scanf("%d%d", &a, &b);
        upz[a] ++;
        upz[b + 1] --;
    }

    LL x = 0LL;
    for(int i = 1; i <= m; i++)
    {
        x += upz[i];
        upt[ zap[i].st.st ] += x * zap[i].nd;
        upt[ zap[i].st.nd + 1 ] -= x * zap[i].nd;
    }

    LL p = 0LL;
    for(int i = 1; i <= n; i++)
    {
        p += upt[i];
        printf("%lld ", p + t[i]);
    }
}
