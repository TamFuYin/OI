#include<bits/stdc++.h>
void ckmax(int& a,int b) {a=std::max(a,b);}
int lowbit(int x){return x&-x;}
const int N=1e3+10,lgN=std::__lg(N)+1;
std::vector<int> to[N];
int fa[N][lgN],dep[N];
void dfs(int u){
	for(int i=1;i<lgN;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int v:to[u]){
		if(v==fa[u][0]) continue;
		fa[v][0]=u;dep[v]=dep[u]+1;
		dfs(v);
	}
}
int walk(int u,int d){
	for(int i=0;i<lgN;i++) if(d>>i&1) u=fa[u][i];
	return u;
}
int LCA(int u,int v){
	if(dep[u]<dep[v]) std::swap(u,v);
	u=walk(u,dep[u]-dep[v]);
	if(u==v) return u;
	for(int i=lgN-1;i>=0;i--)
		if(fa[u][i]!=fa[v][i])
			u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
std::vector<std::pair<int,int> > ch[N];
int f[N][1<<10],g[N];
void upd(int u,int w){
	g[u]+=w;
	for(int v:to[u]){
		if(v==fa[u][0]) continue;
		upd(v,w);
	}
}
int bh[N];
int mx1[10],mx2[10][10];
void solve(int u){
	int sz=0;
	for(int v:to[u]){
		if(v==fa[u][0]) continue;
		solve(v);
		bh[v]=sz++;
	}
	memset(mx1,0,sizeof mx1);
	memset(mx2,0,sizeof mx2);
	for(auto p:ch[u]){
		int x=p.first,y=p.second;
		if(x==u) ckmax(mx1[bh[walk(y,dep[y]-dep[u]-1)]],g[y]+1);
		// ,printf("mx1[%d] <- %d\n",walk(y,dep[y]-dep[u]-1),g[y]+1);
		else{
			int ux=bh[walk(x,dep[x]-dep[u]-1)],uy=bh[walk(y,dep[y]-dep[u]-1)];
			ckmax(mx2[std::min(ux,uy)][std::max(ux,uy)],g[x]+g[y]+1);
			// printf("mx2[%d,%d] <- %d\n",walk(x,dep[x]-dep[u]-1),walk(y,dep[y]-dep[u]-1),g[x]+g[y]+1);
		}
	}
	for(int s=0;s<(1<<sz);s++){
		for(int v:to[u]){
			if(v==fa[u][0]) continue;
			if(s>>bh[v]&1^1) f[u][s]+=f[v][0];
		}
	}
	for(int s=(1<<sz)-1;s;s--)
		for(int i=0;i<sz;i++) if(s>>i&1){
			ckmax(f[u][s^1<<i],f[u][s]+mx1[i]);
			for(int j=i+1;j<sz;j++) if(s>>j&1)
				ckmax(f[u][s^1<<i^1<<j],f[u][s]+mx2[i][j]);
			}
	for(int v:to[u]){
		if(v==fa[u][0]) continue;
		upd(v,f[u][1<<bh[v]]);
	}
	g[u]=f[u][0];
	 // for(int s=0;s<(1<<sz);s++)if(f[u][s]){
		 // printf("f[%d][",u);
		 // for(int v:to[u]){
			 // if(v==fa[u][0]) continue;
			 // if(s>>bh[v]&1) printf("%d,",v);
		 // }
		 // printf("]=%d\n",f[u][s]);
	 // }
}
int main(){
	freopen("celebration.in","r",stdin);
	freopen("celebration.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),
		to[u].push_back(v),to[v].push_back(u);
	dfs(1);
	int m;scanf("%d",&m);
	int ans=0;
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		if(u==v) {++ans;continue;}
		if(dep[u]>dep[v]) std::swap(u,v);
//		printf("LCA(%d,%d)=%d\n",u,v,LCA(u,v));
		ch[LCA(u,v)].emplace_back(u,v);
	}
	solve(1);
	printf("%d",f[1][0]+ans);
}
