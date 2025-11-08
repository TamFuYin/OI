#include<bits/stdc++.h>
const int N=1e5+10,MOD=998244353,HALF=(MOD+1)/2;
#define pb push_back
std::vector<int> to[N];
int fac[N+1],ifac[N+1],hf[N+1];
int ans;
bool dfs(int u,int fa=0){
	int d=to[u].size()&1;
	for(int v:to[u]){
		if(v==fa) continue;
		d+=dfs(v,u);
	}
	if(d>=2){
		// printf("%d %d %lld\n",u,d,1ll*fac[d^(d&1)]%MOD*ifac[d/2]%MOD*hf[d/2]%MOD*(d&1?d:1));
		ans=1ll*ans*fac[d^(d&1)]%MOD*ifac[d/2]%MOD*hf[d/2]%MOD;
		if(d&1) ans=1ll*ans*d%MOD;
	}
	return d&1;
}
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return ret;
}
int main(){
	fac[0]=1;for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	ifac[N]=qpow(fac[N],MOD-2);for(int i=N;i>=1;i--) ifac[i-1]=1ll*ifac[i]*i%MOD;
	hf[0]=1;for(int i=1;i<=N;i++) hf[i]=1ll*hf[i-1]*HALF%MOD;
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++) to[i].clear();
		for(int i=1,u,v;i<n;i++)
			scanf("%d%d",&u,&v),
			to[u].pb(v),to[v].pb(u);
		ans=1;dfs(1);
		printf("%d\n",ans);
	}
}