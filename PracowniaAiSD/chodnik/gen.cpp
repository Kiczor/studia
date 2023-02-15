#include <cstdio>
#include <cstdlib>
#include <sys/time.h>

using namespace std;

int val( int a, int b )
{
    return rand() % ( b - a + 1 ) + a;
}

int main()
{
    timeval czas;
    gettimeofday( &czas, 0 );
    srand( czas.tv_sec * 1000 + czas.tv_usec * 100 );

    int n = val( 100000, 200000 );
    //int n = val( 1, 10 );
    printf("%d\n", n);
    for(int i = 0; i < n; i++)
    {
        //printf("%d %d %d\n", val( 0, 5 ), val( 0, 5 ), val( 0, 5 ) );
        printf("%d %d %d\n", val( 0, 100 ), val( 0, 100 ), val( 0, 100 ) );
    }
}