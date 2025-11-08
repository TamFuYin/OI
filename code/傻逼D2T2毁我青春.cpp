#include<bits/stdc++.h>
#define mms(x) memset(x,0,sizeof x)
#define mmc(x,y) memcpy(x,y,sizeof y)
#define for_ss(i,S) for(int i=((S)-1)&(S);i;i=(i-1)&(S))
#define for_sse(i,S) for(int i=S;i;i=(i-1)&(S))
int lowbit(int x){return x&-x;}
const int N=15;
namespace DSU{
	int pa[N],sz[N];
	void clear(){
		std::iota(pa,pa+N,0);
		std::fill(sz,sz+N,1);
	}
	int findp(int u){
		if(pa[u]==u) return u;
		return pa[u]=findp(pa[u]);
	}
	void merge(int u,int v){
		u=findp(u),v=findp(v);
		if(u==v) return;
		if(sz[u]<sz[v]) std::swap(u,v);
		sz[u]+=sz[v],pa[v]=u;
	}
}
using namespace DSU;
std::vector<std::pair<int,int> > edges[N*N];
std::bitset<N*N> ne[1<<N];
int cnt(int S,int T){return (ne[S]&ne[T]).count();}
int sc[1<<N],nsc[1<<N];
double be[1<<N];
double phf[N*N];
double f[1<<N],g[1<<N];
double dp[1<<N];
int main(){
	phf[0]=1;for(int i=1;i<N*N;i++) phf[i]=phf[i-1]/2;
	int c,T;scanf("%d%d",&c,&T);
	while(T--){
		clear();
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1,u,v,w;i<=m;i++)
			scanf("%d%d%d",&u,&v,&w),
			--u,--v,edges[w].emplace_back(u,v);
		for(int S=0;S<(1<<n);S++) be[S]=1,sc[S]=S;
		for(int i=1;i<=m;i++){
			mms(ne);
			bool ok=0;
			for(unsigned j=0;j<edges[i].size();j++){
				int u,v;std::tie(u,v)=edges[i][j];
				if(sc[1<<u]==sc[1<<v]) continue;
				ok=1;
				merge(u,v);
				ne[1<<u].set(j);
				ne[1<<v].set(j);
			}
			if(!ok) continue;
			for(int S=1;S<(1<<n);S++)
				ne[S]=ne[S-lowbit(S)]|ne[lowbit(S)];
			mms(nsc);
			for(int j=0;j<n;j++) nsc[1<<findp(j)]|=1<<j;
			for(int j=0;j<n;j++) nsc[1<<j]=nsc[1<<findp(j)];
			for(int S=1;S<(1<<n);S++) nsc[S]=nsc[S^lowbit(S)]|nsc[lowbit(S)];
			mms(f),mms(g);
			for(int S=1;S<(1<<n);S++){
				f[S]=1;
				for_ss(T,S) if(!(sc[S^T]&sc[T])&&lowbit(S)==lowbit(T))
					g[S]-=g[S^T]*f[T]*phf[2*cnt(sc[S^T],sc[T])];
				for_sse(T,S) if(!(sc[S^T]&sc[T]))
					f[S]-=g[T]*phf[cnt(T,sc[S^T])];
				g[S]+=f[S];
				printf("%d f=%.2lf g=%.2lf\n",S,f[S],g[S]);
			}
			mms(dp);
			for(int j=0;j<n;j++)if(pa[j]==j){
				dp[nsc[1<<j]]=1;
				for_sse(S,nsc[1<<j])
					for_ss(T,S) if(!(sc[S^T]&sc[T]))
						dp[S^T]-=dp[S]*phf[cnt(sc[S^T],T)]*be[T];
				for_sse(S,nsc[1<<j]) dp[S]*=be[S];
				for(int k=0;k<n;k++) if(nsc[1<<j]>>k&1)
					for_sse(S,nsc[1<<j]) if(S>>k&1)
						dp[S^(1<<k)]+=dp[S];
				for(int S=1;S<(1<<n);S++) printf("%d dp=%.2lf\n",S,dp[S]);
				for_sse(S,nsc[1<<j]){
					be[S]=dp[S]*f[S];
					for_sse(T,(1<<n)-1^nsc[1<<j])
						be[S^T]=be[S]*be[T];
				}
			}
			for(int S=1;S<(1<<n);S++) printf("%d be=%.2lf dp=%.2lf\n",S,be[S],dp[S]);
			mmc(sc,nsc);
		}
		double ans=0;
		for(int i=0;i<n;i++)
			for(int S=0;S<(1<<n);S++)
				if(S>>i&1) be[S^(1<<i)]-=be[S];
		for(int S=1;S<(1<<n);S++) ans+=be[S],printf("%d be=%.2lf\n",S,be[S]);
		printf("%.2lf\n",ans);
	}
}