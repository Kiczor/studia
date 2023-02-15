#include <cstdio>
#include <algorithm>

using namespace std;

int n;

int main()
{
    scanf("%d", &n);
    int pop = 0;
    for(int i = 0; i < n; i++)
    {
        int l, m, r;
        scanf("%d%d%d", &l, &m, &r);

        if( i == 0 && l != 0 )
            printf("wynik nie zaczyna sie od zera\n");
        if( i == n - 1 && r != 0 )
            printf("wynik nie konczy sie zerem\n");
        
        if( l != pop )
            printf("chodnik sie nie laczy\n");
        
        pop = r;
    }

    printf("OK");
}