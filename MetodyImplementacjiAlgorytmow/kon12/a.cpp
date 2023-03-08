#include <cstdio>
#include <algorithm>

using namespace std;

int n, m, wynik;

int main()
{
	scanf("%d%d", &n, &m);
	for(int a = 0; a <= max( n, m ); a++)
		for(int b = 0; b <= max( n, m ); b++)
		{
			if( a * a + b == n && a + b * b == m )
				wynik ++;
		}

	printf("%d", wynik);
}
