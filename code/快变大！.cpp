#include<bits/stdc++.h>
#define ckmin(a,b) a=std::min(a,b)
#define ckmax(a,b) a=std::max(a,b)
const int N=101,M=2601;
using ll=long long;
int v[N],t[N];
const ll INF=1e18;
ll f[2][N][M*2];
int n,k;
int main(){
	freopen("enlarge.in","r",stdin);
	freopen("enlarge.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d%d",v+i,t+i);
	for(int u=0;u<=k;u++)
		for(int a=0;a<M*2;a++)
			f[0][u][a]=-INF;
	f[0][0][M]=0;
	for(int i=1;i<=n;i++){
		for(int u=0;u<=k;u++){
			for(int a=0;a<M*2;a++){
				f[i&1][u][a]=f[i-1&1][u][a];
				if(a+t[i]<M*2) ckmax(f[i&1][u][a],f[i-1&1][u][a+t[i]]+v[i]);
				if(a-t[i]>=0) ckmax(f[i&1][u][a],f[i-1&1][u][a-t[i]]+v[i]);
				if(a+2*t[i]<M*2&&u) ckmax(f[i&1][u][a],f[i-1&1][u-1][a+2*t[i]]+v[i]);
				if(a-2*t[i]>=0&&u) ckmax(f[i&1][u][a],f[i-1&1][u-1][a-2*t[i]]+v[i]);
			}
		}
	}
	ll ans=0;
	for(int i=0;i<=k;i++) ckmax(ans,f[n&1][i][M]);
	printf("%lld",ans);
}
