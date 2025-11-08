/*
连通块的问题很难处理，
但是如果我们要求连通块包含根，
那么类似一个高维最大前缀和问题，
可以在欧拉序上 DP 处理
要求包含某个点，
这正是点分治之主旨
*/
#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
#define ALL(x) x.begin(),x.end()
const int N=4e4+10,K=3e3+10;
int a[N];
std::vector<int> to[N],rto[N];
bool vis[N];
int siz[N];
int n,k;
int getC(int u,int size,int fa=0){
	int tmp=0,mxs=0;
	siz[u]=1;
	for(int v:to[u]){
		if(v==fa||vis[v]) continue;
		tmp|=getC(v,size,u);
		siz[u]+=siz[v];
		ckmax(mxs,siz[v]);
	}
	return std::max(mxs,size-siz[u])<=size/2?u:tmp;
}
int f[N][K],g[N][K],dep[N],ans[N];
const int INF=1e9;
void clear(int u,int fa=0){
	std::fill(f[u],f[u]+k+1,-INF);
	std::fill(g[u],g[u]+k+1,-INF);
	for(int v:to[u]){
		if(v==fa||vis[v]) continue;
		clear(v,u);
	}
}
void dfs(int u,int fa=0){
	if(dep[u]==k) return;
	for(int v:to[u]){
		if(v==fa||vis[v]) continue;
		for(int i=2;i<=k;i++)
			f[v][i]=f[u][i-1]+a[v];
		dep[v]=dep[u]+1;
		dfs(v,u);
		for(int i=1;i<=k;i++)
			ckmax(f[u][i],f[v][i]);
	}
}
void rdfs(int u,int fa=0){
	for(int i=1;i<=k;i++)
		ckmax(ans[u],f[u][i]+g[u][k-i+dep[u]]-f[u][dep[u]]);
	assert(f[u][dep[u]]==g[u][dep[u]]);
	if(dep[u]==k) return;
	for(int v:rto[u]){
		if(v==fa||vis[v]) continue;
		for(int i=2;i<=k;i++)
			g[v][i]=g[u][i-1]+a[v];
		rdfs(v,u);
		for(int i=1;i<=k;i++)
			ckmax(g[u][i],g[v][i]);
	}
}
void dfz(int u,int size){
//	printf("DFZ %d\n",u);
	dep[u]=1;
	clear(u);
	f[u][1]=g[u][1]=a[u];
	dfs(u);rdfs(u);
	vis[u]=1;
	for(int v:to[u]){
		if(vis[v]) continue;
		int vsz=siz[v]>siz[u]?size-siz[u]:siz[v];
		dfz(getC(v,vsz),vsz);
	}
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),
		to[u].push_back(v),
		to[v].push_back(u);
	for(int i=1;i<=n;i++) rto[i]=to[i],std::reverse(ALL(rto[i]));
	dfz(getC(1,n),n);
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
}
