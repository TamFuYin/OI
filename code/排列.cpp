#include<bits/stdc++.h>
const int N=3e3+10,MOD=1e9+7;
char s[N];
int f[N][N],g[N][N];
int main(){
	int n;scanf("%d%s",&n,s+2);
	f[1][1]=g[1][1]=1;
	for(int i=2;i<=n;i++){
		if(s[i]=='<'){
			for(int k=2;k<=i;k++)
				(f[i][k]+=g[i-1][k-1])%=MOD;
		}
		else{
			for(int k=1;k<=i-1;k++)
				(f[i][k]+=(g[i-1][i-1]-g[i-1][k-1]+MOD)%MOD)%=MOD;
		}
		for(int j=1;j<=i;j++) g[i][j]=(g[i][j-1]+f[i][j])%MOD;
	}
	int ans=0;
	for(int i=1;i<=n;i++) (ans+=f[n][i])%=MOD;
	printf("%d",ans);
}