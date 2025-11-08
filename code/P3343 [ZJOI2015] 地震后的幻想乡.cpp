#include<bits/stdc++.h>
const int N=10;
int f[1<<N][(N-1)*N/2+1],d[1<<N];
std::vector<std::pair<int,int> > E;
/*
f[S][i] 表示 S 的导出子图有多少个边数为 i 的不连通生成子图
枚举 S 的编号最小的点所在的连通块，然后转移。
*/
int lowbit(int x){return x&-x;}
int fac[N+1];
int binom(int n,int k){return fac[n]/fac[n-k]/fac[k];}
int main(){
	for(int i=1;i<=N;i++) fac[i]=fac[i-1]*i;
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		E.emplace_back(u,v);
	}
	for(int S=1;S<(1<<n);S++)
		for(auto[u,v]:E) d[S]+=S>>u-1&S>>v-1&1;
	for(int S=1;S<(1<<n);S++){
		for(int T=(S-1)&S;T;T=(T-1)&S)
		if(lowbit(S)==lowbit(T)){
			for(int i=0;i<=m;i++){
				for(int j=0;j<=i;j++){
					f[S][i]+=(binom(d[T],j)-f[T][j])*f[S^T][i-j];
				}
			}
		}
	}
	double ans=0;
	for(int i=0;i<=m;i++){
		for(int j=0;j<=m;j++){
			ans+=f[(1<<n)-1][i]*(j&1?-1:1)*binom(m-i,j)*1./(i+j+1);
		}
	}
	printf("%d",ans);
}
