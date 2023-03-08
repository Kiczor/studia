#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string s;
int n;

void solve()
{
    cin >> n;
    cin >> s;

    int a = 0, b = n - 1;
    while( a < b )
    {
        if( abs( s[a] - s[b] ) > 2 || abs( s[a] - s[b] ) == 1 )
        {
            cout << "NO\n";
            return;
        }
        a ++;
        b --;
    }

    cout << "YES\n";
}

int main()
{
    int q; cin >> q;
    while( q -- )
    {
        solve();
        s.clear();
    }
}
