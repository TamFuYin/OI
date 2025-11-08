#include<bits/stdc++.h>
#define ckmin(a,b) a=std::min(a,b)
const int N=2e5+10,W=2e5,lgN=std::__lg(N)+1;
std::vector<int> to[N];
int fa[N][lgN],dep[N];
void makefa(int u){
	for(int i=1;i<lgN;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int v:to[u]){
		if(v==fa[u][0]) continue;
		dep[v]=dep[u]+1;
		fa[v][0]=u;
		makefa(v);
	}
}
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
using ll=long long;
struct node{
	int ls,rs,min;ll vl,vr;
	node():ls(0),rs(0),vl(0),vr(0),min(INT_MAX){}
}t[N*10];int size;
ll solvel(int o,int k,int l,int r){
	if(!o) return 0;
	if(l==r) return t[o].min<k?l:0;
	int mid=l+r>>1;
	if(k<t[t[o].ls].min) return solvel(t[o].rs,k,mid+1,r);
	return solvel(t[o].ls,k,l,mid)+t[o].vr;
}
ll solver(int o,int k,int l,int r){
	if(!o) return 0;
	if(l==r) return t[o].min<k?l:0;
	int mid=l+r>>1;
	if(k<t[t[o].rs].min) return solver(t[o].ls,k,l,mid);
	return solver(t[o].rs,k,mid+1,r)+t[o].vl;
}
ll askl(int o,int& k,int L,int R,int l=1,int r=W){
	if(!o||L>R) return 0;
	int mid=l+r>>1,ret=0;
	if(L<=l&&r<=R){
		ret=solvel(o,k,l,r);
		// printf(">>> %d[%d,%d]: %d\n",k,l,r,ret);
		ckmin(k,t[o].min);
		return ret;
	}
	if(L<=mid) ret=askl(t[o].ls,k,L,R,l,mid);
	if(mid<R) ret+=askl(t[o].rs,k,L,R,mid+1,r);
	return ret;
}
ll askr(int o,int& k,int L,int R,int l=1,int r=W){
	if(!o||L>R) return 0;
	int mid=l+r>>1,ret=0;
	if(L<=l&&r<=R){
		ret=solver(o,k,l,r);
		// printf(">>> [%d,%d]%d: %d\n",l,r,k,ret);
		ckmin(k,t[o].min);
		return ret;
	}
	if(mid<R) ret=askr(t[o].rs,k,L,R,mid+1,r);
	if(L<=mid) ret+=askr(t[o].ls,k,L,R,l,mid);
	return ret;
}
void pushup(int o,int l,int r){
	int mid=l+r>>1;
	t[o].vl=solver(t[o].ls,t[t[o].rs].min,l,mid);
	t[o].vr=solvel(t[o].rs,t[t[o].ls].min,mid+1,r);
	t[o].min=std::min(t[t[o].ls].min,t[t[o].rs].min);
}
void insert(int& o,int x,int v,int l=1,int r=W){
	if(!o) o=++size;
	if(l==r) return t[o].min=v,void();
	int mid=l+r>>1;
	if(x<=mid) insert(t[o].ls,x,v,l,mid);
	else insert(t[o].rs,x,v,mid+1,r);
	pushup(o,l,r);
}
void de1ete(int& o,int x,int l=1,int r=W){
	if(l==r) return o=0,void();
	int mid=l+r>>1;
	if(x<=mid) de1ete(t[o].ls,x,l,mid);
	else de1ete(t[o].rs,x,mid+1,r);
	pushup(o,l,r);
	if(t[o].min==INT_MAX) o=0;
}
void merge(int& o,int p,int l=1,int r=W){
	if(!p) return;
	if(!o) {o=p;return;}
	if(l==r) return;
	int mid=l+r>>1;
	merge(t[o].ls,t[p].ls,l,mid);
	merge(t[o].rs,t[p].rs,mid+1,r);
	pushup(o,l,r);
}
int getv(int o,int x,int l=1,int r=W){
	if(!o) return INT_MAX;
	if(l==r) return t[o].min;
	int mid=l+r>>1;
	if(x<=mid) return getv(t[o].ls,x,l,mid);
	else return getv(t[o].rs,x,mid+1,r);
}
//void print(int o,int l=1,int r=W){
//	if(!o) return;
//	if(l==r){
//		printf("%d,%d ",l,t[o].min);
//		return;
//	}
//	int mid=l+r>>1;
//	print(t[o].ls,l,mid);
//	print(t[o].rs,mid+1,r);
//}
#define add(u,v) to[u].push_back(v)
std::vector<std::pair<int,int> > ins[N],ask[N];
std::vector<int> del[N];
int rt[N];
ll ans[N];
void dfs(int u){
	for(int v:to[u]){
		if(v==fa[u][0]) continue;
		dfs(v);
		merge(rt[u],rt[v]);
	}
	#define x first
	#define t second
	for(auto p:ins[u]) insert(rt[u],p.x,p.t);
	for(auto p:del[u]) de1ete(rt[u],p);
	for(auto p:ask[u]){
		int tmp,t=p.t,at=getv(rt[u],p.x);
		if(at<t) ans[p.t]+=p.x,t=at;
		ans[p.t]+=askr(rt[u],tmp=t,1,p.x-1);
		ans[p.t]+=askl(rt[u],tmp=t,p.x+1,W);
	}
	#undef x
	#undef t
}
int main(){
	std::cin.tie(0);std::ios::sync_with_stdio(0);
	int n,m;std::cin>>n>>m;
	for(int i=1,u,v;i<n;i++)
		u=i,v=i+1,add(u,v),add(v,u);
	makefa(1);
	for(int i=1,opt;i<=m;i++){
		std::cin>>opt;
		if(opt==1){
			int u,v,w;std::cin>>u>>v>>w;
			ins[u].emplace_back(w,i);
			ins[v].emplace_back(w,i);
			del[fa[LCA(u,v)][0]].emplace_back(w);
			ans[i]=-1;
		}
		else{
			int u,w;std::cin>>u>>w;
			ask[u].emplace_back(w,i);
		}
	}
	dfs(1);
	for(int i=1;i<=m;i++)
		if(ans[i]!=-1) std::cout<<ans[i]<<'\n';
}
