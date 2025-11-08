#include<bits/stdc++.h>
namespace poly{
	const int N=1e6+10,MOD=998244353;
	using ll=long long;
	int Add(int x,int y){return x+y<MOD?x+y:x+y-MOD;}
	int Sub(int x,int y){return x<y?x-y+MOD:x-y;}
	void Pls(int& x,int y){x=Add(x,y);}
	void Dec(int& x,int y){x=Sub(x,y);}
	int Mul(int x,int y){return (ll)x*y%MOD;}
	int qpow(int a,int b){
		int ret=1;
		while(b){
			if(b&1) ret=Mul(ret,a);
			a=Mul(a,a);b>>=1;
		}
		return ret;
	}
	int fac[N+1],ifac[N+1];
	int r[N],G[N*2];
	void preproc(){
		fac[0]=1;for(int i=1;i<=N;i++) fac[i]=Mul(fac[i-1],i);
		ifac[N]=qpow(fac[N],MOD-2);for(int i=N;i>=1;i--) ifac[i-1]=Mul(ifac[i],i);
		for(int k=2,w;k<N;k<<=1){
			w=qpow(3,(MOD-1)/k),G[k]=1;
			for(int i=1;i<k/2;i++) G[k+i]=Mul(G[k+i-1],w);
		}
	}
	int binom(int n,int k){
		return Mul(Mul(fac[n],ifac[n-k]),ifac[k]);
	}
	int L;
#define len (1<<L)
	void FWT(int f[]){
		for(int k=2,x,y;k<=len;k<<=1)
			for(int i=0;i<len;i+=k)
				for(int j=i;j<i+k/2;j++)
					x=f[j],y=f[j+k/2],
					f[j]=Add(x,y),f[j+k/2]=Sub(x,y);
	}
	void IFWT(int f[]){
		FWT(f);int inv=MOD-(MOD-1)>>L;
		for(int i=0;i<len;i++) f[i]=Mul(f[i],inv);
	}
	void pre(int n=len){
		while(len<=n) ++L;
		for(int i=1;i<len;i++) r[i]=r[i>>1]+(i&1)*len>>1;
	}
	void DFT(int f[]){
		for(int i=0;i<len;i++) if(r[i]<i) std::swap(f[i],f[r[i]]);
		for(int k=2,x,y;k<=len;k<<=1)
			for(int i=0;i<len;i+=k)
				for(int j=i;j<i+k/2;j++)
					x=f[j],y=Mul(f[j+k/2],G[k+j-i]),
					f[j]=Add(x,y),f[j+k/2]=Sub(x,y);
	}
	void IDFT(int f[]){
		DFT(f),std::reverse(f+1,f+len);
		for(int w=MOD-(MOD-1)>>L,i=0;i<len;i++) f[i]=Mul(f[i],w);
	}
	void conv(int c[],int a[],int b[]){
		DFT(a),DFT(b);
		for(int i=0;i<len;i++) c[i]=Mul(a[i],b[i]);
		IDFT(c);
	}
}
using namespace poly;
int a[N],b[N],f[N],g[N],h[N];
int main(){
//	freopen("set.in","r",stdin);
//	freopen("set.out","w",stdout);
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	preproc();
	for(int i=1,ai;i<=n;i++) scanf("%d",&ai),++a[ai];
	for(int i=n-k;i<=n-(k+1)/2;i++)
		f[i]=Mul(Mul(qpow(2,2*n-i-k),binom(n-i,k-(n-i))),ifac[i]),g[i]=ifac[i];
	for(int i=0;i<=n;i++) printf("%d ",f[i]);puts("");
	for(int i=0;i<=n;i++) printf("%d ",g[i]);puts("");
	pre(n*2);conv(h,f,g);
	for(int i=0;i<=n;i++) h[i]=n-i&1?MOD-h[i]:h[i];
	for(int i=0;i<=n;i++) printf("%d ",h[i]);puts("");
	L=m;FWT(a);
	for(int i=0;i<(1<<m);i++) printf("%d ",a[i]);puts("");
	for(int s=0;s<(1<<m);s++) b[s]=h[(a[s]+n)%MOD/2];
	IFWT(b);
	for(int s=0;s<(1<<m);s++) printf("%d ",b[s]);
}
