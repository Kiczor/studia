#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> PII;
#define f first
#define s second
#define pb push_back
const int N = 1e6+1;
int n,K;
int t[N];
string s;

int f(int a){
	return s[a]-'0';
}

int main(){
	std::ios_base::sync_with_stdio(false);
	cin>>s;
	n = s.size();
	for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) for(int k=j+1;k<n;k++){
		K = 100*f(i) + 10*f(j) + f(k);
		//cout<<K<<endl;
		if(K%8==0){
			cout<<"YES\n";//<<K;
			return 0;
		}
	}
	for(int i=0;i<n;i++) for(int j=i+1;j<n;j++){
		K = 10*f(i) + f(j);
		//cout<<K<<endl;
		if(K%8==0){
			cout<<"YES\n";//<<K;
			return 0;
		}
	}
	for(int i=0;i<n;i++) if(s[i] == '8' || s[i] == '0') { cout<<"YES\n"/*<<s[i]*/; return 0; }
	cout<<"NO";

}
