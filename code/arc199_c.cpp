#include<bits/stdc++.h>
const int N=5e2+10;
const int MOD=998244353;
int n;
template<typename T>
void ckmin(T& a,T b){a=std::min(a,b);}
template<typename T>
void ckmax(T& a,T b){a=std::max(a,b);}
struct perm{
	int p[N];
	void read(){
		for(int i=1;i<=n;i++) scanf("%d",p+i);
	}
	perm inv(){
		static perm ret;
		for(int i=1;i<=n;i++) ret.p[p[i]]=i;
		return ret;
	}
	perm operator*(const perm& b)const{
		static perm ret;
		for(int i=1;i<=n;i++) ret.p[i]=p[b.p[i]];
		return ret;
	}
	void norm(){//normalize
		for(int i=2;i<=n;i++) p[i]=(p[i]-p[1]+n)%n+1;
		p[1]=1;
	}
	void print(){
		for(int i=1;i<=n;i++) printf("%d ",p[i]);puts("");
	}
}p[N];
bool law[N][N];
int f[N][N],g[N][N];
int main(){
	int m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) p[i].read();
	static perm p1i=p[1].inv();//p1i.print();
	for(int i=1;i<=m;i++) p[i]=p[i]*p1i,p[i].norm();//,p[i].print();
	memset(law,0xff,sizeof law);
	for(int i=2;i<=m;i++)
		for(int l=1;l<=n;l++){
			int min=INT_MAX,max=INT_MIN;
			for(int r=l;r<=n;r++){
				ckmin(min,p[i].p[r]);
				ckmax(max,p[i].p[r]);
				law[l][r]&=max-min==r-l;
			}
		}
	for(int i=1;i<=n+1;i++) g[i][i-1]=1;
	for(int l=n;l>=2;l--){
		for(int r=l;r<=n;r++){
			if(law[l][r])
				for(int i=l;i<=r;i++)
					(f[l][r]+=1ll*g[l][i-1]*g[i+1][r]%MOD)%=MOD;
			for(int i=l;i<=r;i++) (g[l][r]+=1ll*g[l][i-1]*f[i][r]%MOD)%=MOD;
			// printf("[%d,%d]=%d,%d\n",l,r,f[l][r],g[l][r]);
		}
	}
	printf("%d",g[2][n]);
}