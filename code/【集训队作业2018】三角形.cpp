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
		return (*this+b).mx<(b+*this).mx;
	}
}t[N*10];int size,ls[N],rs[N];
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
int nxt[N],end[N];
data a[N];
int it[N];
int pa[N];
int findp(int x){
	if(x==pa[x]) return x;
	return pa[x]=findp(pa[x]);
}
int bh[N];
int rt[N];
data O;
void dfs(int u){
	insert(rt[u],bh[u],a[u]);
	for(int v:to[u]){
		dfs(v);
		merge(rt[u],rt[v]);
	}
	ans[u]=(data{w[u],w[u]}+t[rt[u]]).mx;
}
int main(){
	int T;scanf("%d%d",&T,&n);
	for(int i=2;i<=n;i++)
		scanf("%d",p+i),to[p[i]].push_back(i),
		printf("%d %d\n",p[i],i);
	for(int i=1;i<=n;i++)
		scanf("%d",w+i);
	for(int i=2;i<=n;i++) sw[p[i]]+=w[i];
	for(int i=1;i<=n;i++) a[i]={sw[i]-w[i],sw[i]};
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			assert(!(a[i]<a[j]&&a[j]<a[i]));
			for(int k=1;k<=n;k++){
				if(a[i]<a[j]&&a[j]<a[k]) assert(a[i]<a[k]);
			}
		}
	}
	std::iota(it+1,it+n+1,1);
	std::sort(it+1,it+n+1,[](int x,int y){return a[x]<a[y]||!(a[y]<a[x])&&x<y;});
	std::iota(pa+1,pa+n+1,1);
	std::iota(end+1,end+n+1,1);
	for(int i=1;i<=n;i++){
		int u=it[i],x=findp(p[u]);
		if(u==1) continue;
//		printf("%d -> %d\n",end[x],u);
		nxt[x]=u;pa[x]=u;
	}
	data tmp={w[1],w[1]};
	for(int i=1,cnt=0;i;i=nxt[i]) bh[i]=++cnt,tmp=tmp+a[i],printf("%d ",i);puts("");
	printf("%d\n",tmp.mx);
	dfs(1);
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);puts("");
}
