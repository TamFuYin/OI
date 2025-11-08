#include<bits/stdc++.h>
const int N=1e6+10,MOD=998244353;
int a[N],s[N];
int inv[N],f[N],g[N];//f[i]=binom(i+k-1,k-1),g[i]=binom(i+k,k)
int main(){
//	freopen("ex_a3.in","r",stdin);
	int n,k;scanf("%d%d",&n,&k);
	inv[1]=1;for(int i=2;i<=n;i++) inv[i]=1ll*(MOD-MOD/i)*inv[MOD%i]%MOD;
	f[0]=1;for(int i=1;i<=n;i++) f[i]=1ll*f[i-1]*(i+k-1)%MOD*inv[i]%MOD;
	g[0]=1;for(int i=1;i<=n;i++) g[i]=1ll*g[i-1]*(i+k)%MOD*inv[i]%MOD;
	for(int i=1;i<=n;i++) scanf("%d",a+i),s[i]=(s[i-1]+a[i])%MOD;
	int ans=0;
	for(int r=1;r<=n;r++) (ans+=1ll*s[r]*f[n-r]%MOD*g[r-1]%MOD)%=MOD;
	for(int l=1;l<n;l++) (ans+=MOD-1ll*s[l]*f[l]%MOD*g[n-l-1]%MOD)%=MOD;
	printf("%d",ans);
}
