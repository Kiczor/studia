#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <map>

#define st first
#define nd second
#define pb push_back
#define mp make_pair

using namespace std;

const int maxn = 1005;

pair<string, string> t[maxn];
string odp[maxn];
int opcja[maxn];
map<string, bool> zab;

bool zle = false;
int n;

bool operator==( string a, string b )
{
    if( a.size() != b.size() ) return false;
    for(int i = 0; i < (int)a.size(); i++)
        if( a[i] != b[i] )
            return false;
    return true;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        string a, b;
        cin >> a >> b;

        t[i].st[0] = a[0];
        t[i].st[1] = a[1];
        t[i].st[2] = a[2];
        t[i].nd[0] = a[0];
        t[i].nd[1] = a[1];
        t[i].nd[2] = b[0];

        printf("%c %c %c\n", t[i].st[0], t[i].st[1], t[i].st[2]);
        printf("%c %c %c\n", t[i].nd[0], t[i].nd[1], t[i].nd[2]);

        cout << t[i].st << endl;
        cout << t[i].nd << endl;
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j < i; j++)
            if( ( t[i].st[0] == t[j].st[0] and t[i].st[1] == t[j].st[1] ) and t[i].st[2] == t[j].st[2] )
            {
                if( ( t[i].nd[0] == t[j].nd[0] and t[i].nd[1] == t[j].nd[1] ) and t[i].nd[2] == t[j].nd[2] )
                    zle = true;
                printf("i:%d j:%d\n", i, j);
                printf("%c %c %c\n", t[i].st[0], t[i].st[1], t[i].st[2]);
                printf("%c %c %c\n", t[j].st[0], t[j].st[1], t[j].st[2]);
                opcja[i] = 1;
                opcja[j] = 1;
                zab[ t[i].st ] = true;
                zab[ t[j].st ] = true;
            }
    }

    for(int i = 1; i <= n; i++)
    {
        if( opcja[i] == 0 )
        {
            if( zab.find( t[i].st ) != zab.end() )
            {
                if( zab.find( t[i].nd ) != zab.end() )
                {
                    zle = true;
                }
                else
                {
                    opcja[i] = 1;
                    zab[ t[i].nd ] = true;
                }
            }
        }
    }

    for(int i = 1; i <= n; i++)
        printf("opcja %d: %d\n", i, opcja[i]);

    if( zle )
    {
        printf("NO");
        return 0;
    }
    else
    {
        printf("YES\n");
        for(int i = 1; i <= n; i++)
        {
            if( opcja[i] == 0 )
                printf("%c%c%c", t[i].st[0], t[i].st[1], t[i].st[2]);
            else
                printf("%c%c%c", t[i].nd[0], t[i].nd[1], t[i].nd[2]);
            printf("\n");
        }
    }
}
