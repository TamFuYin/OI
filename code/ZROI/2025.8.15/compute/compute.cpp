#include<bits/stdc++.h>
const int N=1e6+10;
char s[N];
int f[N],lasA[N],lasB[N],lasAB[N];
const int MOD=998244353;
int main(){
	int n;scanf("%d%s",&n,s+1);
	f[0]=1;
	lasA[n+1]=lasA[n+2]=lasB[n+1]=lasB[n+2]=lasAB[n+1]=lasAB[n+2]=n+1;
	s[0]='A';
	for(int i=n;i>=1;i--){
		lasA[i]=s[i]=='A'?i:lasA[i+2];
		lasB[i]=s[i]=='B'?i:lasB[i+2];
		lasAB[i]=s[i-1]=='A'&&s[i]=='B'?i:lasAB[i+2];
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		if(s[i]=='A') (f[lasA[i+1]]+=f[i])%=MOD,(f[lasAB[i+1]]+=f[i])%=MOD;
		else (f[lasA[i+1]]+=f[i])%=MOD,(f[lasB[i+1]]+=f[i])%=MOD;
		if(n-i&1^1) (ans+=f[i])%=MOD;
//		printf("%d ",f[i]);
	}
//	puts("");
	if(s[n]=='B'){
		for(int i=n-1;i;i-=2){
			if(s[i-1]=='A'&&s[i]=='A') (ans+=MOD-f[i-1])%=MOD;
			if(s[i-1]=='A'&&s[i]=='B') break;
		}
	}
	printf("%d",ans);
}
