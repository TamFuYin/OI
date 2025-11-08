#include<bits/stdc++.h>
using ll=long long;
const int N=1000,MOD=998244353;
int d[N];
std::pair<int,int> c[N];
int tot,n,s=1;
std::map<int,int> mp;
int fac[N+1],ifac[N+1];
int binom(int n,int k){
	if(k>n) return 0;
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
int _pow[N][N];
int all(int s){
	int ret=1;
	for(int i=1;i<=n;i++){
		int k=s%(c[i].second+1);s/=c[i].second+1;
		ret=1ll*ret*binom(c[i].second,k)%MOD*_pow[i][k]%MOD;
	}
	return ret;
}
int coprime(int s,int t){
	int ret=1;
	for(int i=1;i<=n;i++){
		int ks=s%(c[i].second+1),kt=t%(c[i].second+1);
		s/=c[i].second+1,t/=c[i].second+1;
		ret=1ll*ret*binom(c[i].second-kt,ks)%MOD*_pow[i][ks]%MOD;
	}
	return ret;
}
void init(){
	fac[0]=1;for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	ifac[N]=qpow(fac[N],MOD-2);for(int i=N;i>=1;i--) ifac[i-1]=1ll*ifac[i]*i%MOD;
}
const int M=128;
struct vector{
	int a[M];
	vector(){memset(a,0,sizeof a);}
}V;
struct matrix{
	int a[M][M];
	matrix(){memset(a,0,sizeof a);}
}f[65];
matrix operator*(const matrix& a,const matrix& b){
	matrix c;
	for(int i=0;i<s;i++){
		for(int j=0;j<s;j++){
			for(int k=0;k<s;k++){
				c.a[i][j]=(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j])%MOD;
			}
		}
	}
	return c;
}
vector operator*(const matrix& a,const vector& b){
	vector c;
	for(int i=0;i<s;i++){
		for(int k=0;k<s;k++){
			c.a[i]=(c.a[i]+1ll*a.a[i][k]*b.a[k])%MOD;
		}
	}
	return c;
}
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	init();
	ll m;scanf("%lld",&m);
	for(int i=2;1ll*i*i<=m;i++) if(m%i==0) for(++tot;m%i==0;++d[tot],m/=i);
	if(m!=1) ++d[++tot];
	for(int i=1;i<=tot;i++) ++mp[d[i]];
	for(auto[a,b]:mp) c[++n]={a,b},s*=b+1;
	for(int i=1;i<=n;i++){
		_pow[i][0]=1;
		for(int j=1;j<=c[i].second;j++)
			_pow[i][j]=1ll*_pow[i][j-1]*c[i].first%MOD;
	}
	int q;scanf("%d",&q);
	for(int i=0;i<s;i++)
		for(int j=0;j<s;j++)
			f[0].a[i][j]=(all(i)+MOD-coprime(i,j))%MOD;
	for(int i=1;i<=60;i++) f[i]=f[i-1]*f[i-1];
	for(int i=0;i<s;i++) V.a[i]=all(i);
	while(q--){
		ll n;scanf("%lld",&n);--n;
		vector Vn=V;int ans=0;
		for(int i=0;n>>i;i++) if(n>>i&1) Vn=f[i]*Vn;
		for(int i=0;i<s;i++) (ans+=Vn.a[i])%=MOD;
		printf("%d\n",ans);
	}
}
