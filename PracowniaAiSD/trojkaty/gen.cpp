#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <map>
#include <vector>

using namespace std;

int mxx = 1e7;
map<pair<int, int>, bool> bylo;

int val( int a, int b )
{
	return rand() % ( b - a + 1 ) + a;
}

int main()
{
	timeval czas;
	gettimeofday( &czas, 0 );
	srand( czas.tv_sec * 1000 + czas.tv_usec * 100 );
	
	int n = val( 8, 10 );
	int l = -10, p = 10;
	printf("%d\n", n);
	for(int i = 0; i < n; i++)
	{
		int a = val( l, p ), b = val( l, p );
		while( bylo.find( make_pair( a, b ) ) != bylo.end() )
		{
			a = val( l, p );
			b = val( l, p );
		}
		printf("%d %d\n", a, b );
	}
}
