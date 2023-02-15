#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

#define mp make_pair
#define st first
#define nd second
#define pb push_back

using namespace std;

const int maxn = 1000005;

int n;
int cntv;

vector< pair<int, char> > G[maxn];  // 1 to start, 2 to akceptujacy

void insert( string s )
{
    if( s[0] == '-' )
        return;
    
    int sz = (int)s.size();
    int u = 1;
    int lastsi = 0;
    for(int i = 1; i < sz; i++) // dopoki sie zgadza
    {
        int nextu = -1;
        for(int j = 0; j < G[u].size(); j++)
            if( G[u][j].nd == s[i] && G[u][j].st != 2 )
                nextu = G[u][j].st;
        if( nextu == -1 )
            break;
        //cout << "u: " << u << ", nextu: " << nextu << ", litera: " << s[i] << endl;
        u = nextu;
        lastsi = i;
    }

    for(int i = lastsi + 1; i < sz - 1; i++) // bez ostatniej literki
    {
        cntv ++;
        G[u].pb( mp( cntv, s[i] ) );
        u = cntv;
    }

    G[u].pb( mp( 2, s[sz - 1] ) );
}

inline void wypisz()
{
    printf("{\n");
    printf("  \"alphabet\"	 : [\"a\", \"b\", \"c\"],\n");
    printf("  \"states\"	 : [\"q1\"");
    for(int i = 2; i <= cntv; i++)
        printf(",\"q%d\"", i);
    printf("],\n");
    printf("  \"initial\"	 : \"q1\",\n");
    printf("  \"accepting\"  : 	[\"q2\"],\n");
    printf("  \"transitions\": [\n");
    for(int i = 1; i < cntv; i++)
    {
        //cerr << "i:" << i << endl;
        for(int j = 0; j < (int)G[i].size(); j++)
            //cerr << "j:" << j << ", G[i][j].st:" << G[i][j].st << ", G[i][j].nd:" << G[i][j].nd << endl;
            printf("        {\"letter\"       : \"%c\", \"from\"        : \"q%d\",\"to\"          : \"q%d\"},\n", G[i][j].nd, i, G[i][j].st);
        //cerr << "po petli" << endl;
        //if( (int)G[i].size() > 0 )
        //    printf("        {\"letter\"       : \"%c\", \"from\"        : \"q%d\",\"to\"          : \"q%d\"}\n", G[i][G[i].size() - 1].nd, i, G[i][G[i].size() - 1].st);
    }
    for(int j = 0; j < (int)G[cntv].size() - 1; j++)
        printf("        {\"letter\"       : \"%c\", \"from\"        : \"q%d\",\"to\"          : \"q%d\"},\n", G[cntv][j].nd, cntv, G[cntv][j].st);
    printf("        {\"letter\"       : \"%c\", \"from\"        : \"q%d\",\"to\"          : \"q%d\"}\n", G[cntv][G[cntv].size() - 1].nd, cntv, G[cntv][G[cntv].size() - 1].st);
    printf("    ]\n");
    printf("}\n");
}

int main()
{
    //ios_base::sync_with_stdio(0);
    cin >> n;
    cntv = 2;
    for(int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        insert( s );
    }

    wypisz();
}