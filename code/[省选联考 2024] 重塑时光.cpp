#include<bits/stdc++.h>
#define lowbit(s) ((s)&-(s))
const int N=16,MOD=1e9+7;
using poly=std::array<int,N+2>;
poly g[1<<N],f[1<<N];
int h[1<<N];
/*
h[S]: 使 S 中点排列成一合法拓扑序的方案数
g[S]: (带符号)S中点形成若干个互相不连边的大点的方案数
f[S]: S中点形成一个合法大点DAG的方案数
*/
poly F;
int n,m,k;
int inv[N*2+1];
poly pre[N+2],suf[N+2];
void lagrange(poly f){
	pre[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			pre[i][j]=1ll*pre[i-1][j]*(MOD-i)%MOD;
			if(j) (pre[i][j]+=pre[i-1][j-1])%=MOD;
		}
	}
	suf[n+2][0]=1;
	for(int i=n+1;i>=2;i--){
		for(int j=0;j<=n;j++){
			suf[i][j]=1ll*suf[i+1][j]*(MOD-i)%MOD;
			if(j) (suf[i][j]+=suf[i+1][j-1])%=MOD;
		}
	}
	for(int i=1;i<=n+1;i++){
		for(int j=1;j<i;j++)
			f[i]=1ll*f[i]*inv[i-j]%MOD;
		for(int j=i+1;j<=n+1;j++)
			f[i]=1ll*f[i]*(MOD-inv[j-i])%MOD;
		for(int j=0;j<=n;j++)
			for(int k=0;j+k<=n;k++)
				(F[j+k]+=1ll*f[i]*pre[i-1][j]%MOD*suf[i+1][k]%MOD)%=MOD;
	}
}
int qpow(int a,int k){
	int b=1;
	while(k){
		if(k&1) b=1ll*b*a%MOD;
		a=1ll*a*a%MOD;k>>=1;
	}
	return b;
}
int fac[N*2+1],ifac[N*2+1];
int binom(int n,int k){
	return 1ll*fac[n]*ifac[n-k]%MOD*ifac[k]%MOD;
}
std::bitset<N*(N-1)/2> in[1<<N],out[1<<N];
int cnt(int s,int t){return (out[s]&in[t]).count();}
int main(){
	inv[1]=1;for(int i=2;i<=N*2;i++) inv[i]=1ll*(MOD-MOD/i)*inv[MOD%i]%MOD;
	fac[0]=1;for(int i=1;i<=N*2;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	ifac[N*2]=qpow(fac[N*2],MOD-2);for(int i=N*2;i>=1;i--) ifac[i-1]=1ll*ifac[i]*i%MOD;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<m;i++){
		int u,v;scanf("%d%d",&u,&v);
		--u,--v;
		for(int s=1;s<(1<<n);s++){
			if(s>>u&1) out[s].set(i);
			if(s>>v&1) in[s].set(i);
		}
	}
	h[0]=1;
	for(int s=1;s<(1<<n);s++){
		for(int i=0;i<n;i++){
			if((s>>i&1)&&!cnt(1<<i,s^1<<i)){
				(h[s]+=h[s^1<<i])%=MOD;
			}
		}
		// printf("%d\n",h[s]);
	}
	for(int j=1;j<=n+1;j++) g[0][j]=MOD-1;
	for(int s=1;s<(1<<n);s++){
		for(int t=s;t;t=(t-1)&s){
			if(lowbit(t)==lowbit(s)&&!cnt(t,s^t)&&!cnt(s^t,t)){
				for(int j=1;j<=n+1;j++) (g[s][j]+=MOD-1ll*g[s^t][j]*j%MOD*h[t]%MOD)%=MOD;
			}
		}
		// printf(">> %d\n",s);
		// for(int j=1;j<=n+1;j++) printf("%d ",g[s][j]);
		// puts("");
	}
	for(int j=1;j<=n+1;j++) f[0][j]=1;
	for(int s=1;s<(1<<n);s++){
		for(int t=s;t;t=(t-1)&s) if(!cnt(t,s^t)){
			for(int j=1;j<=n+1;j++) (f[s][j]+=1ll*f[s^t][j]*g[t][j]%MOD)%=MOD;
		}
	}
	// for(int i=1;i<=n+1;i++) printf("%d ",f[(1<<n)-1][i]);puts("->");
	lagrange(f[(1<<n)-1]);
	// for(int i=0;i<=n;i++) printf("%d ",F[i]);puts("");
	int ans=0;
	for(int i=1;i<=n&&i<=k+1;i++){
		int tmp=0;
		for(int j=0;j<=i-1;j++)
			(tmp+=1ll*(j&1?MOD-1:1)*binom(i-1,j)%MOD*fac[i-j+k]%MOD*ifac[i-j]%MOD)%=MOD;
		(ans+=1ll*tmp*fac[i]%MOD*F[i]%MOD)%=MOD;
		// printf(">>> %d\n",ans);
	}
	ans=1ll*ans*ifac[n+k]%MOD;
	printf("%d",ans);
}