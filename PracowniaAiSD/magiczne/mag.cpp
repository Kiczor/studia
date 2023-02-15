#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1000005;
const int INF = 1e9 + 5;

vector<int> t;

int mediana( int a, int b, int c, int d, int e )
{
    //printf("a:%d, b:%d, c:%d, d:%d, e:%d\n", a, b, c, d, e);
    vector<int> temp = {a, b, c, d, e};
    sort( temp.begin(), temp.end() );
    /*for(int i = 0; i < temp.size(); i++)
        printf("%d ", temp[i]);
    printf("\n");*/
    return temp[2];
}

int magia( vector<int> v, int k )
{
    //printf("\nv: "); for(int i = 0; i < (int)v.size(); i++) printf("%d ", v[i]); printf("  k:%d\n", k);
    if( (int)v.size() < 6 )
    {
        sort( v.begin(), v.end() );
        return v[k - 1];
    }

    while( (int)v.size() % 5 != 0 )
        v.push_back( INF );

    int vs = (int)v.size();

    vector<int> p;
    //p.resize( vs / 5 + 2 );
    for(int i = 0; i < vs; i += 5)
        p.push_back( mediana( v[i], v[i + 1], v[i + 2], v[i + 3], v[i + 4] ) );

    /*printf("p: ");
    for(int i = 0; i < p.size(); i++)
        printf("%d ", p[i]);
    puts("");*/
    
    int m = magia( p, ((int)p.size() + 1) / 2 );

    vector<int> mniejsze, rowne, wieksze;
    for(int i = 0; i < vs; i++)
    {
        if( v[i] < m )
            mniejsze.push_back( v[i] );
        if( v[i] == m )
            rowne.push_back( v[i] );
        if( v[i] > m )
            wieksze.push_back( v[i] );
    }

    /*printf("mniejsze:\n");
    for(int i = 0; i < mniejsze.size(); i++)
        printf("%d ", mniejsze[i]);
    printf("\nrowne:\n");
    for(int i = 0; i < rowne.size(); i++)
        printf("%d ", rowne[i]);
    printf("\nwieksze:\n");
    for(int i = 0; i < wieksze.size(); i++)
        printf("%d ", wieksze[i]);
    puts("");*/
    
    if( (int)mniejsze.size() >= k )
    {
        //puts("if 1");
        return magia( mniejsze, k );
    }
    else
    {
        if( (int)mniejsze.size() + (int)rowne.size() >= k)
        {
            //puts("if 2");
            return m;
        }
        else
        {
            //puts("if 3");
            return magia( wieksze, k - (int)mniejsze.size() - (int)rowne.size() );
        }
    }
}

int main()
{
    int N, K;
    scanf("%d%d", &N, &K);
    t.resize( N );
    for(int i = 0; i < N; i++)
        scanf("%d", &t[i]);

    printf("%d", magia( t, K ) );
}