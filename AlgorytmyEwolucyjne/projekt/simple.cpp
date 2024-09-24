#include <cstdio>
#include <algorithm>

#define ll long long int

using namespace std;

ll n, m, boardsize;
int turns;

inline void printboard(ll board)
{
    printf("board:\n");
    for(ll i = 0; i < boardsize; i++)
    {
        if( (1 << i) & board )
            printf("#");
        else
            printf(".");

        if( (i + 1) % m == 0 )
            printf("\n");
    }
}

ll simulation(ll board)
{
    int t[n][m];
    for(ll i = 0LL; i < n; i++)
        for(ll j = 0LL; j < m; j++)
            t[i][j] = ((board & (1LL << (i * m + j))) != 0) ? 1 : 0;

    //printboard(board);
    /*for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            printf("%d", t[i][j]);
        printf("\n");
    }*/

    for( int turn = 0; turn < turns; turn++ )
    {
        int newt[n][m];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
            {
                int neighbours = 0;

                for(int x = i - 1; x <= i + 1; x++)
                    for(int y = j - 1; y <= j + 1; y++)
                        if( (x >= 0 && x < n) && (y >= 0 && y < m) )
                            if( !(x == i && y == j) && t[x][y] == 1 )
                                neighbours ++;

                if( neighbours == 3 )
                    newt[i][j] = 1;
                else if( neighbours == 2 && t[i][j] == 1 )
                    newt[i][j] = 1;
                else
                    newt[i][j] = 0;
                    
                if( board == 251 ) printf("%d, %d, neighbours:%d, t:%d, newt:%d\n", i, j, neighbours, t[i][j], newt[i][j]);
            }
        
        
        if( board == 251 )
        {
            printf("t:\n");
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                    printf("%d", t[i][j]);
                printf("\n");
            }
            printf("newt:\n");
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                    printf("%d", newt[i][j]);
                printf("\n");
            }
        }

        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                t[i][j] = newt[i][j];
    }

    ll res = 0LL;
    for(ll i = 0LL; i < n; i++)
        for(ll j = 0LL; j < m; j++)
            if( t[i][j] == 1 )
                res += (1LL << (i * m + j));

    //printf("result (%d)", __builtin_popcount(res));
    //printboard(res);
    return res;
}

int main()
{
    scanf("%lld%lld%d", &n, &m, &turns);
    boardsize = n * m;

    int bestresult = 0;
    ll bestboard = 0;
    for(ll mask = 0; mask < (1LL << boardsize); mask++)
    {
        int result = __builtin_popcount( simulation( mask ) );
        if( result > bestresult )
        {
            bestboard = mask;
            bestresult = result;
        }

        if( __builtin_popcount(mask) == 1LL )
        {
            printf("mask: %lld, best result: %d\n", mask, bestresult);
        }
    }

    printboard(bestboard);
    printf("after simulation ");
    printboard(simulation(bestboard));
    printf("best result: %d, bitmask:%lld", bestresult, bestboard);
}