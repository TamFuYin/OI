#include<bits/stdc++.h>
const int N=3e5+10;
using ll=long long;
int fa[N],p[N];
struct edge{int f,s,w;}e[N];
bool operator<(const edge& a,const edge& b){return a.w<b.w;}
int getp(int x){return p[x]=x==p[x]?x:getp(p[x]);}
int wet[N],rt[N],dfn[N],dfncnt,last,siz[N];ll tot[N];
std::vector<int> son[N];
void dfs(int u){
	dfn[u]=++dfncnt;
	siz[u]=1;
	for(int v:son[u])
		dfs(v),siz[u]+=siz[v];
}
int q[N],ind[N];
int n,size;
void solve(){
	int head=0,tail=0;
	for(int i=1;i<=n;i++) ++ind[fa[i]],siz[i]=1;
	for(int i=1;i<=n;i++) if(!ind[i]) q[++tail]=i;
	while(head<tail){
		int u=q[++head];siz[fa[u]]+=siz[u];
		if(!--ind[fa[u]]) q[++tail]=fa[u];
	}
	head=0,tail=1;
	dfn[q[1]=1]=1;
	while(head<tail){
		int u=q[++head],last=0;
		for(int v:son[u]){
			if(!last) dfn[v]=dfn[u]+1;
			else dfn[v]=dfn[last]+siz[last];
			q[++tail]=last=v;
		}
	}
}
struct node{int ls,rs;ll sum;}t[N*4];
void add(const int& p,const ll& v,int& o=last,int l=1,int r=n){
	if(!p) return;
	t[++size]=t[o];
	t[size].sum+=v;
	o=size;
	if(l==r) return;
	const int& mid=l+r>>1;
	if(p<=mid) add(p,v,t[o].ls,l,mid);
	else add(p,v,t[o].rs,mid+1,r);
}
ll query(const int& o,const int& L,const int& R,int l=1,int r=n){
	if(!o||L<=l&&r<=R) return t[o].sum;
	int mid=l+r>>1;ll ret=0;
	if(L<=mid) ret+=query(t[o].ls,L,R,l,mid);
	if(mid<R) ret+=query(t[o].rs,L,R,mid+1,r);
	return ret;
}
int main(){
	freopen("fire9.in","r",stdin);
//	freopen("fire.out","w",stdout);
	int id,T;
	scanf("%d%d%d",&id,&n,&T);
	std::iota(p+1,p+n+1,1);
	for(int i=2,w;i<=n;i++)
		scanf("%d%d",&fa[i],&w),
		e[i-1]={fa[i],i,w},
		son[fa[i]].push_back(i);
	solve();
	std::sort(e+1,e+n);
	for(int i=1;i<n;i++){
		int u=getp(e[i].f),v=e[i].s,w=e[i].w;
		p[v]=u;tot[u]+=tot[v]+w;
		add(dfn[fa[v]],tot[v]+w);
		add(dfn[fa[u]],-tot[v]-w);
		// printf("%d %d %d %d\n",last,dfn[fa[v]],dfn[fa[u]],tot[v]+w);
		rt[i]=last;wet[i]=w;
	}
	int q;ll lastans=0;
	scanf("%d",&q);
	while(q--){
		int u,k;lastans&=(1<<20)-1;
		scanf("%d%d",&u,&k);
		if(T) u^=lastans,k^=lastans;
		// printf("> %d %d~%d\n",rt[std::upper_bound(wet+1,wet+n,k)-wet-1],dfn[u],dfn[u]+siz[u]-1);
		printf("%lld\n",lastans=query(rt[std::upper_bound(wet+1,wet+n,k)-wet-1],dfn[u],dfn[u]+siz[u]-1));
	}
}
