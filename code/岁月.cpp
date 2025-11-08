#include<bits/stdc++.h>
const int N=15,M=N*N/2;
std::vector<std::pair<int,int> > e[N];
int pa[N],sz[N];
int bl[N][N],bs[N][N];
int c[N];
std::bitset<M> to[1<<N];
int cnt(int S,int T){
	return (to[S]&to[T]).count();
}
const int MOD=1e9+7,I2=(MOD+1)/2;
int f[N][1<<N];
int bc[N];
int lowbit(int s){return s&-s;}
int main(){
	int c,T;scanf("%d%d",&c,&T);
	while(T--){
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1,u,v,w;i<=m;i++) scanf("%d%d%d",&u,&v,&w),e[w].emplace_back(u,v);
		std::iota(pa+1,pa+n+1,1);std::fill(sz+1,sz+n+1,1);
		for(int i=1;i<=n;i++) bl[0][i]=i,bs[0][i]=1<<i-1,f[0][1<<i-1]=1;
		for(int v=1;v<=m;v++){
			for(auto p:e[v])
				if(findp(p.first)!=findp(p.second))
					merge(p.first,p.second);
			for(int i=1;i<=n;i++)
				bl[v][i]=findp(i),
				bs[v][findp(i)]|=1<<i-1;
			for(int i=0;i<(1<<n);i++) to[i].reset();
			int _m=0;for(auto p:e[v]) to[1<<p.first-1].set(_m),to[1<<p.second-1].set(_m),_m++;
			for(int s=1;s<(1<<n);s++) to[s]=to[s^lowbit(s)]|to[lowbit(s)];
			for(int sb=1;sb<=n;sb++){
				int s=bs[v][sb];
				for(int r=s;r;r=(r-1)&s){
				}
			}
		}
	}
}
