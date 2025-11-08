#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
#define ckmin(a,b) a=std::min(a,b)
using ll=long long;
//const int MAXN=5e7+10,MOD=1e9+7;
//int Add(int x,int y){return x+y<MOD?x+y:x+y-MOD;}
//int Sub(int x,int y){return x<y?x-y+MOD:x-y;}
//void Pls(int& x,int y){x=Add(x,y);}
//void Dec(int& x,int y){x=Sub(x,y);}
//int Mul(int x,int y){return (ll)x*y%MOD;}
//int qpow(int a,int b){
//	int ret=1;
//	while(b){
//		if(b&1) ret=Mul(ret,a);
//		a=Mul(a,a);b>>=1;
//	}
//	return ret;
//}
//int fac[MAXN+1],ifac[MAXN+1];
//int inv[MAXN];
//void preproc(){
//	fac[0]=1;for(int i=1;i<=MAXN;i++) fac[i]=Mul(fac[i-1],i);
//	ifac[MAXN]=qpow(fac[MAXN],MOD-2);for(int i=MAXN;i>=1;i--) ifac[i-1]=Mul(ifac[i],i);
//	inv[1]=1;
//	for(int i=2;i<MAXN;i++) inv[i]=Mul(MOD-MOD/i,inv[MOD%i]);
//}
//int r[MAXN],G[MAXN*2];
//void DFTinit(){
//	for(int k=2,w;k<MAXN;k<<=1){
//		w=qpow(3,(MOD-1)/k),G[k]=1;
//		for(int i=1;i<k/2;i++) G[k+i]=Mul(G[k+i-1],w);
//	}
//}
//int binom(int n,int k){
//	return Mul(Mul(fac[n],ifac[n-k]),ifac[k]);
//}
//int L;
//#define len (1<<L)
//void FWT(int f[]){
//	for(int k=2,x,y;k<=len;k<<=1)
//		for(int i=0;i<len;i+=k)
//			for(int j=i;j<i+k/2;j++)
//				x=f[j],y=f[j+k/2],
//				f[j]=Add(x,y),f[j+k/2]=Sub(x,y);
//}
//void IFWT(int f[]){
//	FWT(f);int inv=MOD-(MOD-1)>>L;
//	for(int i=0;i<len;i++) f[i]=Mul(f[i],inv);
//}
//void pre(int n=len){
//	while(len<=n) ++L;
//	for(int i=1;i<len;i++) r[i]=r[i>>1]+(i&1)*len>>1;
//}
//void DFT(int f[]){
//	for(int i=0;i<len;i++) if(r[i]<i) std::swap(f[i],f[r[i]]);
//	for(int k=2,x,y;k<=len;k<<=1)
//		for(int i=0;i<len;i+=k)
//			for(int j=i;j<i+k/2;j++)
//				x=f[j],y=Mul(f[j+k/2],G[k+j-i]),
//				f[j]=Add(x,y),f[j+k/2]=Sub(x,y);
//}
//void IDFT(int f[]){
//	DFT(f),std::reverse(f+1,f+len);
//	for(int w=MOD-(MOD-1)>>L,i=0;i<len;i++) f[i]=Mul(f[i],w);
//}
//void conv(int c[],int a[],int b[]){
//	DFT(a),DFT(b);
//	for(int i=0;i<len;i++) c[i]=Mul(a[i],b[i]);
//	IDFT(c);
//}
//bool MillerRabin(ll n){
//	if(n<3||n%2==0) return n==2;
//	if(n%3==0) return n==3;
//	ll u=n-1,t=0;
//	while(u%2==0) u/=2,++t;
//	for(int i=0;i<10;i++){
//		ll a=rnd()%(n-3)+2,v=qpow(a,u,n);
//		if(v==1) continue;
//		ll s;
//		for(s=0;s<t;s++){
//			if(v==n-1) break;
//			v=(ll)v*v%n;
//		}
//		if(s==t) return 0;
//	}
//	return 1;
//}
//ll PollardRho(int n){
//	for(ll c=(ll)rnd()%(n-1)+1,goal=1,
//		s=0,t=0,val=1,d;;goal*=2,s=t,val=1){
//		for(ll step=1;step<=goal;step++){
//			t=(qmul(t,t,n)+c)%n;
//			val=qmul(val,abs(t-s),n);
//			if(step%127==0&&(d=gcd(val,n))>1)
//				return d;
//		}
//		if((d=gcd(val,n))>1) return d;
//	}
//}
//std::vector<int> p;
//bool np[MAXN];
//void EulerSieve(){
//	for(int i=2;i<MAXN;i++){
//		if(!np[i]) p.push_back(i);
//		for(int j:p){
//			if(1ll*i*j>=MAXN) break;
//			np[i*j]=1;
//			if(i%j==0) break;
//		}
//	}
//}
const int M=120,N=105;
int m,mm;
struct bitset{
	bool a[M];
	void read(){
		static char s[M];
		scanf("%s",s);
		for(int i=m-1;i>=0;i--) a[i]=s[m-i-1]-'0';
	}
	void print(){
		for(int i=mm-1;i>=0;i--) printf("%d",(int)a[i]);
		puts("");
	}
	bitset operator+(const bitset& b)const{
		bool res=0;
		static bitset c;
		for(int i=0;i<mm;i++) c.a[i]=a[i]^b.a[i]^res,res=((int)a[i]+b.a[i]+res)/2;
		assert(!res);
		return c;
	}
	bool operator<(const bitset& b)const{
		for(int i=mm-1;i>=0;i--)
			if(a[i]<b.a[i]) return 1;
			else if(b.a[i]<a[i]) return 0;
		return 0;
	}
	bool operator<=(const bitset& b)const{
		return !(b<*this);
	}
	bitset operator-(const bitset& b)const{
		static bitset c;
		bool res=0;
		for(int i=0;i<mm;i++) c.a[i]=a[i]^b.a[i]^res,res=a[i]<(int)b.a[i]+res;
//		assert(!res);
		return c;
	}
	bitset ceildiv2()const{
		static bitset c;
		c=*this;
		int i=0;
		while(c.a[i]) c.a[i++]=0;
		c.a[i]=1;
		for(int i=0;i<mm;i++) c.a[i]=c.a[i+1];
		return c;
	}
	int lgceil(){
		int i=mm-1;
		while(!a[i]) --i;
		for(int j=0;j<i;j++) if(a[j]) return i+1;
		return i;
	}
}a[N],s[N],sum,tmp,u;
std::priority_queue<bitset> Q;
int main(){
	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	int n,q;scanf("%d%d%d",&n,&m,&q);mm=m+20;
	for(int i=1;i<=n;i++) a[i].read(),s[i]=s[i-1]+a[i];
	while(q--){
		int l,r,cur=0,ans=0;scanf("%d%d",&l,&r);
		for(int i=l;i<=r;i++) Q.push(a[i]);//,a[i].print();
		sum=s[r]-s[l-1];
//		sum.print();
		while(!Q.empty()){
			u=Q.top();Q.pop();
			if(Q.empty()&&u.lgceil()==0){
				ckmax(ans,cur);
				break;
			}
			tmp=sum.ceildiv2();
			printf("tmp=");tmp.print();
			printf("u=");u.print();
			++cur;
			printf("%d %d %d\n",cur,ans,Q.size());
			if(tmp<u){
				ckmax(ans,cur+tmp.lgceil());
				u=u-tmp,sum=sum-tmp;
//				printf("u\'=");u.print();
				Q.push(u);
			}
			else sum=sum-u,ckmax(ans,cur+u.lgceil());
		}
		printf("%d\n",ans);
	}
}
