#include<bits/stdc++.h>
const int M=50;
int a[M];
const int MOD=1e9+9;
using ll=long long;
int m;
struct vector{
	int a[M];
	vector operator*(const int b)const{
		static vector c;
		for(int i=0;i<m;i++) c.a[i]=(ll)a[i]*b%MOD;
		return c;
	}
	vector operator+(const vector b)const{
		static vector c;
		for(int i=0;i<m;i++) c.a[i]=(a[i]+b.a[i])%MOD;
		return c;
	}
};
struct matrix{
	int a[M][M];
	vector operator*(const vector& b)const{
		static vector c;
		for(int i=0;i<m;i++){
			c.a[i]=0;
			for(int j=0;j<m;j++)
				c.a[i]=(c.a[i]+(ll)a[i][j]*b.a[j])%MOD;
		}
		return c;
	}
	matrix operator*(const matrix& b)const{
		static matrix c;
		for(int i=0;i<m;i++)
			for(int k=0;k<m;k++){
				c.a[i][k]=0;
				for(int j=0;j<m;j++)
					c.a[i][k]=(c.a[i][k]+(ll)a[i][j]*b.a[j][k])%MOD;
			}
		return c;
	}
	void print(){
		for(int i=0;i<m;i++,puts(""))
			for(int j=0;j<m;j++) printf("%d ",a[i][j]);
		puts("");
	}
};
const int V=1e9+8,B=pow(V,1./3),BB=B*B;
matrix A1[B],Ab[B],Abb[B],I;
vector x,tmp;
int main(){
//	freopen("ex_linear7.in","r",stdin);
	freopen("linear.in","r",stdin);
	freopen("linear.out","w",stdout);
	int n;scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d",a+i);
	for(int i=0;i<m;i++) I.a[i][i]=1;
	A1[0]=Ab[0]=Abb[0]=I;
	for(int i=0;i<m;i++) A1[1].a[0][i]=a[i+1];
	for(int i=1;i<m;i++) A1[1].a[i][i-1]=1;
	for(int i=2;i<B;i++) A1[i]=A1[i-1]*A1[1];
	Ab[1]=A1[B-1]*A1[1];
	for(int i=2;i<B;i++) Ab[i]=Ab[i-1]*Ab[1];
	Abb[1]=Ab[B-1]*Ab[1];
	for(int i=2;i<B;i++) Abb[i]=Abb[i-1]*Abb[1];
	x.a[0]=1;
	for(int i=1,b,c;i<=n;i++)
		scanf("%d%d",&b,&c),
		x=(x+Abb[b/BB]*(Ab[b/B%B]*(A1[b%B]*(x*c))));
	printf("%d",x.a[0]);
}
