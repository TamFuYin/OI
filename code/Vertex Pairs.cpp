#include<bits/stdc++.h>
const int N=4e5+10,lgN=std::__lg(N)+1;
std::vector<int> to[N];
int siz[N];
int n,rt=1e9;
void getG(int u,int fa=0){
	siz[u]=1;
	int mx=0;
	for(int v:to[u]){
		if(v==fa) continue;
		getG(v,u);
		siz[u]+=siz[v];
		mx=std::max(mx,siz[v]);
	}
	if(std::max(mx,n-siz[u])<=n/2)
		rt=std::min(rt,u);
}
int fa[N][lgN],dep[N];
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
int dfn[N],dfncnt;
void dfs(int u){
	siz[u]=1;
	dfn[u]=++dfncnt;
	for(int i=1;i<lgN;i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int v:to[u]){
		if(v==fa[u][0]) continue;
		fa[v][0]=u;
		dep[v]=dep[u]+1;
		dfs(v);
		siz[u]+=siz[v];
	}
}
int las[N],frn[N];
int lowbit(int x){return x&-x;}
int t[N];
void add(int x,int v){
	while(x<=n){
		t[x]+=v;
		x+=lowbit(x);
	}
}
int ask(int x){
	int v=0;
	while(x){
		v+=t[x];
		x-=lowbit(x);
	}
	return v;
}
bool vis[N];
void del(int u){
	add(dfn[LCA(u,frn[u])],-1);
	add(dfn[frn[u]],1);
	vis[u]=1;
	for(int v:to[u]){
		if(v==fa[u][0]||vis[v]) continue;
		del(v);
	}
}
std::vector<int> ans;
int a[N];
int main(){
	scanf("%d",&n);n*=2;
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),
		to[u].push_back(v),
		to[v].push_back(u);
	getG(1);
	dfs(rt);
	// printf("%d\n",rt);
	// return 0;
	for(int i=1;i<=n;i++){
		if(las[a[i]]){
			int j=las[a[i]];
			frn[i]=j;frn[j]=i;
			add(dfn[LCA(i,j)],1);
		}
		else las[a[i]]=i;
	}
	for(int i=n;i>=1;i--)
		if(vis[i]) continue;
		else if(ask(dfn[i]-1)==ask(dfn[i]+siz[i]-1))
			del(i),vis[i]=1;
		else ans.push_back(i);
	printf("%d\n",(int)ans.size());
	std::reverse(ans.begin(),ans.end());
	for(auto i:ans) printf("%d ",i);
}