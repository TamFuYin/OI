#define rep(i,l,r) for(int i=l;i<=r;i++)
#define drep(i,r,l) for(int i=r;i>=l;i--)
#include<bits/stdc++.h>
const int N=1<<13,MOD=998244353;
int fac[N+1],ifac[N+1];
int binom(int n,int k){
	if(k<0||k>n) return 0;
	return 1ll*fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
}
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return ret;
}
int rev[FN];
void NTT(int a[]){
}
int main(){
	rep(i,0,N-1) rev[i]=rev[i>>1]>>1|(i&1?N>>1:0);
	fac[0]=1;rep(i,1,N) fac[i]=1ll*fac[i-1]*i%MOD;
	ifac[N]=qpow(fac[N],MOD-2);drep(i,N,1) ifac[i-1]=1ll*ifac[i]*i%MOD;
	int n;scanf("%d",&n);
	int l=1;f[0]=1;NTT(f);
	rep(i,1,n){
		int a,b;scanf("%d%d",&a,&b);
		l+=a-b;
		rep(i,) g[i]=binom(a+b,b+i);
		rep(j,1,l[i&1]){
			f[i&1][j]=0;
			rep(k,1,l[i&1^1]){
				(f[i&1][j]+=1ll*f[i&1^1][k]*binom(a+b,b+j-k)%MOD)%=MOD;
			}
		}
	}
	int ans=0;
	rep(i,1,l[n&1]) (ans+=f[n&1][i])%=MOD;
	printf("%d",ans);
}