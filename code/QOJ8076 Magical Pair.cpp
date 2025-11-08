#include<bits/stdc++.h>
const int MOD=998244353;
using ll=long long;
std::mt19937_64 rnd(time(0));
ll qmul(ll a,ll b,ll mod=MOD){
	return (__int128)a*b%mod;
}
ll qpow(ll a,ll b,ll mod=MOD){
	ll c=1;
	while(b){
		if(b&1) c=qmul(c,a,mod);
		a=qmul(a,a,mod),b>>=1;
	}
	return c;
}
ll gcd(ll a,ll b){
	return b==0?a:gcd(b,a%b);
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
const int N=1e6;
bool np[N];
void preproc(){
	for(int i=2;i<N;i++){
		if(!np[i]) p.push_back(i);
		for(int j:p){
			if(1ll*i*j>=N) break;
			np[i*j]=1;
			if(i%j==0) break;
		}
	}
}
ll pf[N];
int pc[N],m;
void factorize(ll n){
	for(int i:p){
		if(n%i==0){
			pf[m++]=i;
			while(n%i==0) n/=i,++pc[m-1];
		}
	}
	if(n==1) return;
	if(!MillerRabin(n)){
		ll x=PollardRho(n);
		assert(MillerRabin(x));
		pf[++m]=x,pc[m]=1;
		n/=x;
		assert(MillerRabin(n));
	}
	pf[++m]=n,pc[m]=1;
}
int code[N];
void decode(int s){
	for(int i=m-1;i>=0;i--){
		code[i]=s%(pc[i]+1);
		s/=pc[i]+1;
	}
}
int recode(){
	int ret=1;
	for(int i=0;i<m;i++)
		ret=ret*(pc[i]+1)+code[i];
	return ret;
}
int f[N];
int main(){
	preproc();
	int T;scanf("%d",&T);
	while(T--){
		ll p;scanf("%lld",&p);
		ll n=p-1,ans=(n%MOD)*(n%MOD)%MOD+((n-1)%MOD)*((n-1)%MOD)%MOD;
		factorize(n);
		int v=1;
		for(int i=0;i<m;i++) v*=pc[i]+1;//,printf("%lld^%d+",pf[i],pc[i]);puts("");
		for(int s=0;s<v;s++){
			decode(s);f[s]=1;
			for(int i=0;i<m;i++)
				f[s]=1ll*f[s]*(qpow(pf[i],pc[i])+(code[i]==pc[i]?MOD-qpow(pf[i],pc[i]-1):0))%MOD;
		}
		for(int i=0;i<m;i++){
			for(int s=0;s<v;s++){
				decode(s);
				if(code[i]!=0){
					int t=recode();
					f[t]+=f[s];
				}
			}
		}
		for(int s=0;s<v;s++){
			ll xs=1;
			for(int i=0;i<m;i++)
				xs=1ll*xs*(qpow(pf[i],pc[i])+(code[i]==pc[i]?MOD-qpow(pf[i],pc[i]-1):0))%MOD;
			ans=(ans+1ll*f[s]*f[s]%MOD*xs)%MOD;
		}
		printf("%d\n",ans);
	}
}
