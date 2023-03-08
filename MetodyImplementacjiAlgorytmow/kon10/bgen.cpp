#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <cstdlib>

using namespace std;

int val( int a, int b )
{
	return a + rand() % ( b - a + 1 );
}

int main()
{
	timeval czas;
	gettimeofday( &czas, 0 );
	srand( czas.tv_sec * 1000 + czas.tv_usec * 100 );

	int len = val( 1, 10 );
	printf("%d", val(1, 9) );
	for(int i = 0; i < len - 1; i++)
		printf("%d", val( 0, 9 ) );
	puts("");
}
