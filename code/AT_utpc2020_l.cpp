#include<bits/stdc++.h>
const int N=1e5;
const int MOD=299993,
I=139302;//160691;
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return ret;
}
int x[N],y[N];
int f[MOD],g[MOD];
int main(){
	int n,z;scanf("%d%d",&n,&z);
	for(int i=1;i<=n;i++)
		scanf("%d%d",x+i,y+i),
		x[i]=(x[i]+1ll*I*y[i])%MOD,
		y[i]=(x[i]+MOD-2ll*I*y[i]%MOD)%MOD;
	for(int i=0;i<MOD;i++){
		int xx=1,yy=1;
		for(int j=1;j<=n;j++)
			xx=1ll*xx*(i+MOD-x[j])%MOD,
			yy=1ll*yy*(i+MOD-y[j])%MOD;
		++f[xx];++g[yy];
	}
	using ll=long long;
	if(z==0){
		printf("%lld",(ll)f[0]*MOD+(ll)g[0]*MOD-(ll)f[0]*g[0]);
		return 0;
	}
	ll ans=0;
	for(int i=1;i<MOD;i++)
		ans+=(ll)f[i]*g[int(1ll*z*qpow(i,MOD-2)%MOD)];
	printf("%lld",ans);
}
