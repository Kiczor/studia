#include <cstdio>
#include <algorithm>
#include <iostream>

#define LL long long int

using namespace std;

LL x;

int main()
{
	string xd;
	cin >> xd;

	if( "NO" == xd )
		return 0;

	scanf("%lld", &x);
	if( x % 8LL != 0LL )
	{
		printf("                            nie8 x:%lld", x);
	}
}
