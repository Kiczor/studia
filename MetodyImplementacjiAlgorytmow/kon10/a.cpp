#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

const int maxn = 100005;

int pref[maxn];

string s;
int n;

int main()
{
	cin >> s;

	s = 'a' + s;

	for(int i = 2; i < s.size(); i++)
	{
		pref[i] = pref[i - 1];
		if( s[i] != s[i - 1] )
			pref[i] ++;
	}

	int q;
	cin >> q;
	while( q -- )
	{
		int a, b;
		scanf("%d%d", &a, &b);

		printf("%d\n", b - a - (pref[b] - pref[a]) );
	}

}
