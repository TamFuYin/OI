#ifndef _POLY
#define _POLY
#include<bits/stdc++.h>
int MOD=998244353,PR=3;
namespace private_namespace_of_poly{
	using ll=unsigned long long;
	int qpow(int a,int b){
		int c=1;
		while(b){
			if(b&1) c=(ll)c*a%MOD;
			a=(ll)a*a%MOD;b>>=1;
		}
		return c;
	}
	int rev[int(1e7)];
	int _max_n=1;
	void initialize(int n){
		for(int i=_max_n;i<=n;i*=2){
			rev[i]=0;
			for(int j=i+1;j<=2*i-1;j++){
				rev[j]=rev[(j-i>>1)+i]>>1|(j-i&1)*(i>>1);
			}
		}
		_max_n=std::max(_max_n,n*2);
	}
}
using namespace private_namespace_of_poly;
struct poly
{
	int *const a;int n;
	poly(int *const a,int n):a(a),n(n){}
	void NTT(bool opt=1){
		initialize(n);
		for(int i=0;i<n;i++) if(rev[n+i]<i) std::swap(a[i],a[rev[n+i]]);
		for(int m=2;m<=n;m*=2){
			const int wm=qpow(PR,(MOD-1)/m*(opt?1:m-1));
			for(int i=0;i<n;i+=m){
				int w=1;
				for(int j=i;j<i+m/2;j++,w=(ll)w*wm%MOD){
					int u=a[j],t=(ll)a[j+m/2]*w%MOD;
					a[j]=(u+t)%MOD;
					a[j+m/2]=(u-t+MOD)%MOD;
				}
			}
		}
		if(!opt){
			int invn=qpow(n,MOD-2);
			for(int i=0;i<n;i++)
				a[i]=(ll)a[i]*invn%MOD;
		}
	}
	#define INTT() NTT(0)
	const int& operator[](const int& x)const{return a[x];}
	int& operator[](const int& x){return a[x];}
	void conv(const poly& f,const poly& g){
		int m=1<<int(ceil(log2(f.n+g.n-1)));
		static int *F=new int[m],*G=new int[m];
		memset(F,0,sizeof(int)*m);
		memset(G,0,sizeof(int)*m);
		memcpy(F,f.a,sizeof(int)*f.n);
		memcpy(G,g.a,sizeof(int)*g.n);
		poly(F,m).NTT();poly(G,m).NTT();
		for(int i=0;i<m;i++) F[i]=(ll)F[i]*G[i]%MOD;
		poly(F,m).INTT();memcpy(a,F,sizeof(int)*n);
		delete[] F;delete[] G;
	}
	void operator*=(const poly& f){
		conv(*this,f);
	}
	void opposite(const poly& f){
		for(int i=0;i<n;i++) a[i]=MOD-f[i];
	}
	void opposite(){opposite(*this);}
	void plus(const poly& f,const poly& g){
		for(int i=0;i<n&&i<f.n&&i<g.n;i++) a[i]=(f[i]+g[i])%MOD;
	}
	void operator+=(const poly& f){plus(*this,f);}
	void operator+=(int x){a[0]=(a[0]+x)%MOD;}
	void diff(const poly& f){
		n=f.n-1;
		for(int i=0;i<n;i++) a[i]=(ll)f[i+1]*(i+1)%MOD;
	}
	void diff(){diff(*this);}
	void inte(const poly& f){
		n=f.n+1;
		for(int i=n-1;i>=1;i--) a[i]=(ll)f[i-1]*qpow(i,MOD-2)%MOD;
		a[0]=0;
	}
	void inte(){inte(*this);}
	void inv(const poly& f){
		static int *g=new int[f.n*2],*h=new int[f.n*2];
		memset(h,0,sizeof(int)*f.n*2);
		h[0]=qpow(f[0],MOD-2);
		for(int m=2;m<=f.n;m*=2){
			memcpy(g,f.a,sizeof(int)*m);
			memset(g+m,0,sizeof(int)*m);
			poly(g,m*2).NTT();
			poly(h,m*2).NTT();
			for(int i=0;i<m*2;i++)
				h[i]=(2*h[i]%MOD-(ll)g[i]*h[i]%MOD*h[i]%MOD+MOD)%MOD;
			poly(h,m*2).INTT();
			memset(h+m,0,sizeof(int)*m);
		}
		memcpy(a,h,sizeof(int)*n);
		delete[] g;delete[] h;
	}
	void inv(){inv(*this);}
	void ln(const poly& f){
		static int *g=new int[n];
		poly(g,n).diff(f);inv(f);
		conv(*this,poly(g,n));
	}
	void ln(){ln(*this);}/*
	void exp(const poly& f){
		static int *g=new int[f.n*2],*h=new int[f.n*2];
		memset(h,0,sizeof(int)*f.n*2);
		h[0]=qpow(f[0],MOD-2);
		for(int m=2;m<=f.n;m*=2){
			poly t(g,m*2);
			t.ln(poly(h,m*2));
			t.opposite();
			t+=poly(f,m);
			t+=1;
			poly(h,m*2)*=t;
			memset(h+m,0,sizeof(int)*m);
		}
		memcpy(a,h,sizeof(int)*n);
		delete[] g;delete[] h;
	}
	void euler(const poly& f){
		memset(a,0,sizeof(int)*(n=f.n));
		for(int m=1;m<=n;m++){
			int invm=qpow(m,MOD-2);
			for(int i=0;i*m<n;i++){
				a[i*m]=(a[i*m]+(ll)f[i]*invm%MOD)%MOD;
			}
		}
		exp();
	}
	void euler(){
		static int *f=new int[n];
		poly(f,n).euler(*this);
		memcpy(a,f,sizeof(int)*n);
	}*/
};
#endif
const int N=1e7;
int a[N],b[N],c[N];
int main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++) scanf("%d",&a[i]);
    for(int i=0;i<=m;i++) scanf("%d",&b[i]);
    poly(c,n+m+1).conv(poly(a,n+1),poly(b,m+1));
    for(int i=0;i<=n+m;i++) printf("%d ",c[i]);
}