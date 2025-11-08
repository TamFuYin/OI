#include<bits/stdc++.h>
const int MOD=1e9+7;
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		b>>=1;a=1ll*a*a%MOD;
	}
	return ret;
}
const int N=1e6;
int f[N],a[N];
int main(){
	int n,mx=0,s=0;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i),(s+=a[i])%=MOD,
		mx=std::max(mx,a[i]);
	f[1]=1ll*(s-1)*(s-1)%MOD*qpow(s,MOD-2)%MOD;
	f[2]=(2*f[1]%MOD-1)%MOD;
	for(int i=3;i<=mx;i++)
		f[i]=((2*f[i-1]%MOD-f[i-2])%MOD-1ll*(s-1)*qpow(s-i+1,MOD-2)%MOD)%MOD;
	int ans=0;
	for(int i=1;i<=n;i++) (ans+=f[a[i]])%=MOD;
	printf("%d",(ans+MOD)%MOD);
}