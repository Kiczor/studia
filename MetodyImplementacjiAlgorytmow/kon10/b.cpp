#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

const int maxn = 105;

string s;
string dp[maxn][10];
int dzies[maxn];

int main()
{
	cin >> s;

	int mnoz = 1;
	for(int i = 0; i <= s.size(); i++)
	{
		dzies[i] = mnoz;
		mnoz = ( mnoz * 10 ) % 8;
	}

	for(int i = s.size() - 1; i >= 0; i--)
	{
		for(int j = 0; j < 8; j++)
			if( dp[i + 1][j].size() > 0 )
				dp[i][j] = dp[i + 1][j];

		dp[i][ ( s[i] - '0' ) % 8 ] = s[i];

		for(int j = 0; j < 8; j++)
		{
			if( dp[i + 1][j].size() > 0 )
				dp[i][ ( j + (s[i] - '0') * dzies[ dp[i + 1][j].size() ] ) % 8 ] = s[i] + dp[i + 1][j];
		}
	}

	printf("dp:\n");
	for(int i = s.size() - 1; i >= 0; i--)
	{
		printf("cyfra: %c\n", s[i]);
		for(int j = 0; j < 8; j++)
			cout << j << " " << dp[i][j] << endl;
	}

	for(int i = 0; i < s.size(); i++)
	{
		if( dp[i][0].size() > 0 && !( dp[i][0][0] == '0' && dp[i][0].size() > 1 ) )
		{
			cout << "YES\n" << dp[0][0];
			return 0;
		}
	}
	cout << "NO\n";
}
