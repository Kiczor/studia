#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int cnt[maxn];

int n, najw;

int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		int a; scanf("%d", &a);
		cnt[a] ++;
		najw = max( najw, a );
	}

	for(int i = 0; i <= najw; i++)
		if( cnt[i] % 2 != 0 )
		{
			printf("Conan\n");
			return 0;
		}

	printf("Agasa\n");
	return 0;
}
