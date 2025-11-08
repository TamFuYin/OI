#include<bits/stdc++.h>
const int MOD=998244353;
const int N=1e6;
int fac[N+10],ifac[N+10],pow2[N+10];
int binom(int n,int k){
	return 1ll*fac[n]*ifac[n-k]%MOD*ifac[k]%MOD;
}
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return ret;
}
int A(int n,int k){
	int ret=0;
	for(int i=0;i<=k;i++)
		(ret+=1ll*(i&1?MOD-1:1)*binom(n+1,i)%MOD*qpow(k+1-i,n)%MOD)%=MOD;
	return ret;
}
int main(){
	fac[0]=1;for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	ifac[N]=qpow(fac[N],MOD-2);for(int i=N;i>=1;i--) ifac[i-1]=1ll*ifac[i]*i%MOD;
	pow2[0]=1;for(int i=1;i<=N;i++) pow2[i]=pow2[i-1]*2%MOD;
	int T;scanf("%d",&T);
	while(T--){
		int n,k;scanf("%d%d",&n,&k);
		printf("%d\n",int(1ll*A(n-1,k-1)*fac[2*n]%MOD*qpow(1ll*n*pow2[n]%MOD,MOD-2)%MOD));
	}
}
