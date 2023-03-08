#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 3005;

bool zlozona[maxn];
vector<int> pierwsze;

int n;

int main()
{
	scanf("%d", &n);

	for(int i = 2; i <= n; i++)
		if( !zlozona[i] )
			for(int j = i + i; j <= n; j += i)
				zlozona[j] = true;

	for(int i = 2; i <= n; i++)
		if( !zlozona[i] )
			pierwsze.push_back( i );

	int wynik = 0;
	for(int x = 1; x <= n; x++)
	{
		int ile = 0;
		for(int i = 0; i < pierwsze.size(); i++)
			if( x % pierwsze[i] == 0 && pierwsze[i] < x )
				ile ++;

		if( ile == 2 )
			wynik ++;
	}

	printf("%d", wynik);
}
