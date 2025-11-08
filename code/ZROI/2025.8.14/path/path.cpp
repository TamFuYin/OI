#include<bits/stdc++.h>
const int N=1e6+10,MOD=998244353;
int fac[N+1],ifac[N+1];
using ll=long long;
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=(ll)ret*a%MOD;
		a=(ll)a*a%MOD;b>>=1;
	}
	return ret;
}
int binom(int n,int k){
	if(k<0||k>n) return 0;
	return (ll)fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
}
int solve(int n,int m,int k){
	if(n+m&1) return (solve(n-1,m,k)+solve(n,m-1,k+(n&1)))%MOD;
	k+=m/2;
	return (ll)binom((n+m)/2,k)*binom((n+m)/2,m-k)%MOD;
}
int main(){
	fac[0]=1;
	for(int i=1;i<=N;i++) fac[i]=(ll)fac[i-1]*i%MOD;
	ifac[N]=qpow(fac[N],MOD-2);
	for(int i=N;i>=1;i--) ifac[i-1]=(ll)ifac[i]*i%MOD;
	int T;scanf("%d",&T);
	while(T--){
		int n,m,k;scanf("%d%d%d",&n,&m,&k);
		printf("%d\n",solve(n,m,k));
	}
}
