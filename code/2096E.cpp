#include<bits/stdc++.h>
const int N=1e5;
char s[N];
int p[N];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d%s",&n,s);
		int m=0,ans=0;
		for(int i=0;i<n;i++) if(s[i]=='B') p[m++]=i;
		for(int i=0;i<m;i++){
			int t=p[i]-i;
			if(t<=1) ans+=t;
			else if(t==3) ans++;
			else ans+=(t+1)/2;
		}
		printf("%d\n",ans);
	}
}
