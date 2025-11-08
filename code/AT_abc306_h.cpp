#include<bits/stdc++.h>
const int N=17,MOD=998244353;
int pa[N],sz[N];
int n,m;
void clear(){
	std::iota(pa,pa+n,0);std::fill(sz,sz+n,1);
}
int findp(int u){
	if(pa[u]==u) return u;
	return pa[u]=findp(pa[u]);
}
bool merge(int u,int v){
	u=findp(u),v=findp(v);
	if(u==v) return 0;
	if(sz[u]<sz[v]) std::swap(u,v);
	sz[u]+=sz[v];pa[v]=u;
	return 1;
}
int f[1<<N],cnt[1<<N];
bool vis[N];
std::pair<int,int> e[N*N];
#define u first
#define v second
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&e[i].u,&e[i].v),--e[i].u,--e[i].v;
	for(int s=1;s<(1<<n);s++){
		cnt[s]=__builtin_popcount(s);
		clear();
		for(int i=1;i<=m;i++)
			if(s>>e[i].u&s>>e[i].v&1) cnt[s]-=merge(e[i].u,e[i].v);
	}
	f[0]=1;
	for(int s=1;s<(1<<n);s++){
		for(int t=s;t;t=(t-1)&s){
			(f[s]+=cnt[t]&1?f[s^t]:MOD-f[s^t])%=MOD;
		}
	}
	printf("%d",f[(1<<n)-1]);
}