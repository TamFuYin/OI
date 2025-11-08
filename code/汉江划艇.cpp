#include<bits/stdc++.h>
const int N=5e2+10,MOD=1e9+7;
int a[N],b[N];
int lsh[N*2],lshn;
int f[2][N*2][N];//在第i位选了在[lsh_j,lsh_{j+1})的数，此前已在这个地方选了k个数
int g[2][N*2];
#define lb(x) std::lower_bound(lsh,lsh+lshn,x)-lsh
int binom[N];
int inv[N];
int main(){
	inv[1]=1;
	for(int i=2;i<N;i++) inv[i]=1ll*(MOD-MOD/i)*inv[MOD%i]%MOD;
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",a+i,b+i);
		lsh[lshn++]=a[i];
		lsh[lshn++]=b[i]+1;
	}
	std::sort(lsh,lsh+lshn);
	lshn=std::unique(lsh,lsh+lshn)-lsh;
	int ans=0;
	for(int i=1;i<=n;i++){
		memcpy(f[i&1],f[i&1^1],sizeof f[0]);
		memcpy(g[i&1],g[i&1^1],sizeof g[0]);
		for(int j=lb(a[i]);lsh[j]<b[i]+1;j++){
			(++f[i&1][j][1])%=MOD;(++g[i&1][j])%=MOD;
			int l=lsh[j+1]-lsh[j];binom[1]=l;
			for(int k=2;k<=i&&k<=l;k++) binom[k]=1ll*binom[k-1]*(l-k+1)%MOD*inv[k]%MOD;
			for(int k=0;k<j;k++){
				(f[i&1][j][1]+=g[i&1^1][k])%=MOD;
				(g[i&1][j]+=1ll*g[i&1^1][k]*binom[1]%MOD)%=MOD;
			}
			for(int k=2;k<=i&&k<=l;k++){
				(f[i&1][j][k]+=f[i&1^1][j][k-1])%=MOD;
				(g[i&1][j]+=1ll*f[i&1^1][j][k-1]*binom[k]%MOD)%=MOD;
			}
		}
	}
	for(int j=0;j<lshn-1;j++) (ans+=g[n&1][j])%=MOD;
	printf("%d",ans);
}