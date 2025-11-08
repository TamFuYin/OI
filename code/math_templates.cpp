#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
#define ckmin(a,b) a=std::min(a,b)
#define mp std::make_pair
using ll=long long;
const int N=5e7+10,MOD=1e9+7;
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
int inv[N];
void preproc(){
	fac[0]=1;for(int i=1;i<=N;i++) fac[i]=Mul(fac[i-1],i);
	ifac[N]=qpow(fac[N],MOD-2);for(int i=N;i>=1;i--) ifac[i-1]=Mul(ifac[i],i);
	inv[1]=1;
	for(int i=2;i<N;i++) inv[i]=Mul(MOD-MOD/i,inv[MOD%i]);
}
int r[N],G[N*2];
int binom(int n,int k){
	return Mul(Mul(fac[n],ifac[n-k]),ifac[k]);
}
int sgn(int x){
	return x&1?MOD-1:1;
}
void DFTinit(){
	for(int k=2,w;k<N;k<<=1){
		w=qpow(3,(MOD-1)/k),G[k]=1;
		for(int i=1;i<k/2;i++) G[k+i]=Mul(G[k+i-1],w);
	}
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
bool MillerRabin(ll n){
	if(n<3||n%2==0) return n==2;
	if(n%3==0) return n==3;
	ll u=n-1,t=0;
	while(u%2==0) u/=2,++t;
	for(int i=0;i<10;i++){
		ll a=rnd()%(n-3)+2,v=qpow(a,u,n);
		if(v==1) continue;
		ll s;
		for(s=0;s<t;s++){
			if(v==n-1) break;
			v=(ll)v*v%n;
		}
		if(s==t) return 0;
	}
	return 1;
}
ll PollardRho(int n){
	for(ll c=(ll)rnd()%(n-1)+1,goal=1,
		s=0,t=0,val=1,d;;goal*=2,s=t,val=1){
		for(ll step=1;step<=goal;step++){
			t=(qmul(t,t,n)+c)%n;
			val=qmul(val,abs(t-s),n);
			if(step%127==0&&(d=gcd(val,n))>1)
				return d;
		}
		if((d=gcd(val,n))>1) return d;
	}
}
std::vector<int> p;
bool np[N];
void EulerSieve(){
	for(int i=2;i<N;i++){
		if(!np[i]) p.push_back(i);
		for(int j:p){
			if(1ll*i*j>=N) break;
			np[i*j]=1;
			if(i%j==0) break;
		}
	}
}
namespace tfx{
	void main(){
	}
}
int main(){
	int T=1;
//	scanf("%d",&T);
	while(T) tfx::main();
}
