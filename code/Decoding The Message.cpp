#include<bits/stdc++.h>
const int MOD=1<<16,mod=1<<15;
int fac[1000];
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return ret;
}
int c[1000];
int main(){
	fac[0]=1;
	for(int i=1;i<1000;i++) fac[i]=1ll*fac[i-1]*i%mod;
	int T;scanf("%d",&T);
	while(T--){
		int k;scanf("%d",&k);
		int n=1<<8;
		memset(c,0,sizeof c);
		while(k--){
			int i,ci;
			scanf("%d%d",&i,&ci);
			c[i]=ci;
		}
		int ans=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				ans=1ll*ans*(c[i]<<8|c[j])%MOD;
			}
		}
		printf(">> %d\n",ans);
		printf("%d\n",qpow(ans,fac[n-2]));
	}
}