#include<bits/stdc++.h>
#define mid ((l+r)>>1)
const int N=2e5+10;
using ll=long long;
struct data{
	ll pl,mx;
	data operator+(const data& b)const{
		return {pl+b.pl,std::max(mx,pl+b.mx)};
	}
	bool operator<(const data& b)const{
		return std::max(mx,pl+b.mx)<std::max(b.mx,b.pl+mx);
	}
}t[N*100];int size,ls[N*100],rs[N*100];
int n;
void pushup(int p){
	t[p]=t[ls[p]]+t[rs[p]];
}
void insert(int& p,int x,data v,int l=1,int r=n){
	if(!p) p=++size;
	if(l==r){
		t[p]=v;
		return;
	}
	if(x<=mid) insert(ls[p],x,v,l,mid);
	else insert(rs[p],x,v,mid+1,r);
	pushup(p);
}
void merge(int& p,int q,int l=1,int r=n){
	if(!q) return;
	if(!p) {p=q;return;}
	assert(l!=r);
	merge(ls[p],ls[q],l,mid);
	merge(rs[p],rs[q],mid+1,r);
	pushup(p);
}
int p[N],w[N];
ll ans[N],sw[N];
std::vector<int> to[N];
int nxt[N],bgn[N],end[N],sz[N],pa[N];
data a[N];
int it[N];
int findp(int x){
	if(x==pa[x]) return x;
	return pa[x]=findp(pa[x]);
}
std::set<std::pair<data,int> > S;
data cur[N];
void combine(int x,int y){
//	int i=17197;assert((pa[i]==i)==(S.find({cur[i],bgn[i]})!=S.end()));
	x=findp(x),y=findp(y);
//	assert(x!=y);
//		if(S.find({cur[x],bgn[x]})==S.end()) fprintf(stderr,"%d %d,%d %d",bgn[x],cur[x].pl,cur[x].mx,sz[x]),exit(-1);
	if(S.find({cur[x],bgn[x]})!=S.end()) S.erase({cur[x],bgn[x]});
	if(S.find({cur[y],bgn[y]})!=S.end()) S.erase({cur[y],bgn[y]});
	data curx=cur[x]+cur[y];
	nxt[end[x]]=bgn[y];
	int bgnx=bgn[x],endx=end[y];
	if(sz[x]<sz[y]) std::swap(x,y);
//	printf("%d(%d) %d(%d)\n",x,bgn[x],y,bgn[y]);
	pa[y]=x;sz[x]+=sz[y];
	bgn[x]=bgnx,end[x]=endx;
	cur[x]=curx;
	cur[y]={0,0};bgn[y]=end[y]=0;
//	printf("%d(%d) %d(%d)\n",x,bgn[x],y,bgn[y]);
	S.emplace(curx,bgnx);
//	assert((pa[i]==i)==(S.find({cur[i],bgn[i]})!=S.end()));
}
int bh[N],rt[N];
void dfs(int u){
	insert(rt[u],bh[u],a[u]);
	for(int v:to[u]){
		dfs(v);
		merge(rt[u],rt[v]);
	}
	ans[u]=(data{w[u],w[u]}+t[rt[u]]).mx;
}
int main(){
	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	int T;scanf("%d%d",&T,&n);
	for(int i=2;i<=n;i++) scanf("%d",p+i),to[p[i]].push_back(i);
	for(int i=1;i<=n;i++) scanf("%d",w+i);
	for(int i=2;i<=n;i++) sw[p[i]]+=w[i];
	for(int i=1;i<=n;i++) cur[i]=a[i]={sw[i]-w[i],sw[i]},S.emplace(cur[i],i);
	for(int i=1;i<=n;i++) sz[pa[i]=bgn[i]=end[i]=i]=1;
	while(S.size()!=1){
		int u=S.begin()->second;
		if(u==1) u=(++S.begin())->second;
		combine(p[u],u);
	}
	int cnt=0;
	for(int i=1;i;i=nxt[i]) bh[i]=++cnt;
	assert(cnt==n);
	dfs(1);
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);puts("");
}
