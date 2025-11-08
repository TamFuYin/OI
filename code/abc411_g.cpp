#include<bits/stdc++.h>
const int MOD=998244353;
int qpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%MOD;
		a=1ll*a*a%MOD;b>>=1;
	}
	return ret;
}
using poly=std::vector<int>;
#define rs resize
#define SZ(x) (int)x.size()
#define up(x) (1<<(int)ceil(log2(x)))
poly mul(poly a,poly b){
	poly c(a.size()+b.size()-1);
	for(int i=0;i<SZ(a);i++)
		for(int j=0;j<SZ(b);j++)
			(c[i+j]+=1ll*a[i]*b[j]%MOD)%=MOD;
	return c;
}
poly lam(auto f,poly a,poly b){
	int mx=std::max(SZ(a),SZ(b));
	a.rs(mx),b.rs(mx);poly c(mx);
	for(int i=0;i<mx;i++) c[i]=f(a[i],b[i]);
	return c;
}
auto sub=[](int x,int y){return x-y;};
poly inv(poly a){
	poly b(1);b[0]=qpow(a[0],MOD-2);
	for(int m=2;m<=SZ(a);m*=2){
		b=mul(b,lam(sub,{2},mul(a,b)));
		b.rs(m);
	}
	return b;
}
const int N=20;
struct matrix{
	int a[N][N];
	matrix operator*(const matrix& b)const{
		matrix c;memset(c.a,0,sizeof c.a);
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				for(int k=0;k<N;k++)
					(c.a[i][k]+=1ll*a[i][j]*b.a[j][k]%MOD)%=MOD;
	}
	int trail(){
		int ret=0;
		for(int i=0;i<N;i++) (ret+=a[i][i])%=MOD;
		return ret;
	}
}A,B;
poly f,g;
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
		scanf("%d%d",&u,&v),--u,--v,
		++A.a[u][v],++A.a[v][u];
	f.resize(up(n));
	B=A*A;
	for(int i=1;i<=n;i++,B=B*A) f[i]=B.trail();
	g=lam(sub,{1},inv(f));
	poly h=mul(f,g);
	for(int i=0;i<SZ(h);i++) printf("%d ",h[i]);
}