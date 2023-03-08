#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

int n;

int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		printf("%d\n", i);
		system("./bgen > test.in");
		system("./bmac < test.in > ok.out");
		system("./b2 < test.in > krab.out");

		/*printf("test:");
		system("cat test.in");
		system("./bcheck < krab.out");*/

		int x = system("diff -bq ok.out krab.out");
		if( x != 0 )
		{
			printf("zle jest\n");

			printf("test:\n");
			system("cat test.in");

			printf("\n\nokej:\n");
			system("cat ok.out");

			printf("\n\nto zle:\n");
			system("cat krab.out");
			break;
		}
	}
}
