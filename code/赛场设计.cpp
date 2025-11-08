#include<bits/stdc++.h>
const int N=1e6;
int P,fac[N+1],ifac[N+1];
int qpow(int n,int k){
	int r=1;
	while(k){
		if(k&1) r=1ll*r*n%P;
		n=1ll*n*n%P;k>>=1;
	}
	return r;
}
int p2[N];
void init(){
	fac[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%P;
	ifac[N]=qpow(fac[N],P-2);
	for(int i=N;i>=1;i--) ifac[i-1]=1ll*ifac[i]*i%P;
	p2[0]=1;
	for(int i=1;i<=N;i++) p2[i]=1ll*p2[i-1]*2%P;
}
int binom(int n,int k){
	return 1ll*fac[n]*ifac[n-k]%P*ifac[k]%P;
}
int f[N][3];
int main(){
	int n;scanf("%d%d",&n,&P);init();
	f[1][1]=1,f[2][1]=2,f[2][2]=1;
	for(int i=3;i<=n;i++){
		f[i][1]=(1ll*f[i-1][1]*p2[i-2]+1ll*f[i-1][2]*p2[i-3])%P;
		f[i][2]=(1ll*f[i-2][1]*p2[2*(i-3)]+(i>3?1ll*f[i-2][2]*p2[2*(i-4)]:0))%P;
		f[i][2]=1ll*f[i][2]*binom(i,2)%P;
	}
	printf("%d",(f[n][1]+f[n][2])%P);
}