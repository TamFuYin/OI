/*
不再恐惧
*/
#include<bits/stdc++.h>
const int MOD=998244353,N=1e7+10;
using ll=long long;
int Add(int x,int y){return x+y<MOD?x+y:x+y-MOD;}
int Sub(int x,int y){return x<y?x-y+MOD:x-y;}
void Pls(int& x,int y){x=Add(x,y);}
void Dec(int& x,int y){x=Sub(x,y);}
int Mul(int x,int y){return (ll)x*y%MOD;}
void Muleq(int& x,int y){x=Mul(x,y);}
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=Mul(ret,a);
		a=Mul(a,a);b>>=1;
	}
	return ret;
}
int fac[N+1],ifac[N+1];
int binom(int n,int k){
	return Mul(Mul(fac[n],ifac[n-k]),ifac[k]);
}
const int K=6e4+10;
int stir2[2][K];
std::vector<std::pair<int,int> > Q[K];
int ans[N];
int main(){
//	freopen("ex_cumulonimbus3.in","r",stdin);
//	freopen("cumulonimbus.out","w",stdout);
	fac[0]=1;for(int i=1;i<=N;i++) fac[i]=Mul(fac[i-1],i);
	ifac[N]=qpow(fac[N],MOD-2);for(int i=N;i>=1;i--) ifac[i-1]=Mul(ifac[i],i);
	int q;scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int n,m,k;scanf("%d%d%d",&n,&m,&k);
		ans[i]=Mul(Mul(fac[m],ifac[m-k]),qpow(Mul(m,qpow(m-1,n-1)),MOD-2));
		Q[n-1].emplace_back(k-1,i);
	}
	for(int i=0;i<K;i++){
		stir2[i&1][0]=i==0;
		for(int j=1;j<=i;j++)
			stir2[i&1][j]=Add(Mul(j,stir2[i&1^1][j]),stir2[i&1^1][j-1]);
		for(auto p:Q[i]) Muleq(ans[p.second],stir2[i&1][p.first]);
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
}
