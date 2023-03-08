#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

const int maxn = 105;

string s;
string dp[maxn][15];

int main()
{
	cin >> s;
	s = 'a' + s;

	for(int i = 1; i < s.size(); i++)
		if( s[i] == '0' )
		{
			printf("YES\n0\n");
			return 0;
		}

	for(int i = 1; i < s.size(); i++)
	{
		for(int j = 0; j < 8; j++)
			if( dp[i - 1][j].size() > 0 )
				dp[i][j] = dp[i - 1][j];

		if( s[i] != '0' )
			dp[i][ ( s[i] - '0' ) % 8 ] = s[i];

		for(int j = 0; j < 8; j++)
		{
			if( dp[i - 1][j].size() > 0 )
				dp[i][ ( j * 10 + s[i] - '0' ) % 8 ] = dp[i - 1][j] + s[i];
		}
	}

	/*printf("dp:\n");
	for(int i = 1; i < s.size(); i++)
	{
		printf("cyfra: %c\n", s[i]);
		for(int j = 0; j < 8; j++)
			cout << j << " " << dp[i][j] << endl;
	}*/

	if( dp[s.size() - 1][0].size() > 0 )
		cout << "YES\n" << dp[s.size() - 1][0];
	else
		cout << "NO\n";
}
