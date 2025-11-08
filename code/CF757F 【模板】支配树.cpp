#include<bits/stdc++.h>
const int N=2e5+10,M=6e5+10,lgN=std::__lg(N)+1;
using ll=long long;
int ls[N];struct edge{int nx,to,va;}e[M];int cnt;
void add(int u,int v,int w){e[++cnt]={ls[u],v,w},ls[u]=cnt;}
std::priority_queue<std::pair<ll,int> > pq;
ll dis[N];
bool vis[N];
std::vector<int> dag[N],t[N];
int deg[N],fa[N][lgN],dep[N];
int q[N];
int LCA(int u,int v){
	if(dep[u]<dep[v]) std::swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=0;i<lgN;i++)
		if(d>>i&1) u=fa[u][i];
	if(u==v) return u;
	for(int i=lgN-1;i>=0;i--)
		if(fa[u][i]!=fa[v][i])
			u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
int siz[N];
void dfs(int u){
	siz[u]=1;
	for(int v:t[u]){
		if(v==fa[u][0]) continue;
		dfs(v);siz[u]+=siz[v];
	}
}
int main(){
	int n,m,s;scanf("%d%d%d",&n,&m,&s);
	for(int i=1,u,v,w;i<=m;i++)
		scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	memset(dis,0x3f,sizeof dis);
	pq.emplace(dis[s]=0,s);
	while(!pq.empty()){
		int u=pq.top().second;pq.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=ls[u],v;i;i=e[i].nx){
			if(dis[v=e[i].to]>dis[u]+e[i].va){
				dis[v]=dis[u]+e[i].va;
				pq.emplace(-dis[v],v);
			}
		}
	}
	for(int u=1;u<=n;u++)if(vis[u]){
		for(int i=ls[u],v;i;i=e[i].nx)
			if(dis[v=e[i].to]==dis[u]+e[i].va)
				dag[u].push_back(v),++deg[v];
	}
	int head=0,tail=1;q[1]=s;
	while(head<tail){
		int u=q[++head];
		if(fa[u][0]){
			dep[u]=dep[fa[u][0]]+1;
			t[fa[u][0]].push_back(u);
			for(int i=1;i<lgN;i++)
				fa[u][i]=fa[fa[u][i-1]][i-1];
		}
		for(int v:dag[u]){
			if(!fa[v][0]) fa[v][0]=u;
			else fa[v][0]=LCA(fa[v][0],u);
			if(!--deg[v]) q[++tail]=v;
		}
	}
	dfs(s);
	int ans=0;
	for(int v:t[s]) ans=std::max(ans,siz[v]);
	printf("%d",ans);
}