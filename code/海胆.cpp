#include<bits/stdc++.h>
const int N=1e5;
using ll=long long;
namespace lct{
	int son[N][2],fa[N],sum[N],val[N],len[N];
	bool tag[N];
	bool isrt(int x){
		return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;
	}
	bool type(int x){
		return son[fa[x]][1]==x;
	}
	void pushup(int x){
		sum[x]=sum[son[x][0]]+sum[son[x][1]]+val[x];
		len[x]=len[son[x][0]]+len[son[x][1]]+1;
	}
	void pushtag(int x){
		std::swap(son[x][0],son[x][1]);tag[x]^=1;
	}
	void pushdown(int x){
		if(tag[x]) pushtag(son[x][0]),pushtag(son[x][1]),tag[x]=0;
	}
	void rotate(int x){
		int f=fa[x];bool k=type(x);
		fa[x]=fa[f];
		if(!isrt(f)) son[fa[f]][type(f)]=x;
		fa[son[x][!k]]=f;
		son[f][k]=son[x][!k];
		son[x][!k]=f;fa[f]=x;
		pushup(f),pushup(x);
	}
	void update(int x){
		if(!isrt(x)) update(fa[x]);
		pushdown(x);
	}
	void splay(int x){
		update(x);
		while(!isrt(x)){
			if(!isrt(fa[x])) rotate(type(fa[x])==type(x)?fa[x]:x);
			rotate(x);
		}
	}
	void access(int x){
		for(int p=0;x;p=x,x=fa[x])
			splay(x),son[x][1]=p,pushup(x);
	}
	void makert(int x){
		access(x);
		splay(x);
		pushtag(x);
	}
	int findrt(int x){
		access(x);
		splay(x);
		while(son[x][0]) x=son[x][0];
		return x;
	}
	bool conn(int u,int v){
		return findrt(u)==findrt(v);
	}
	void add(int u,int v){
		makert(u);
		splay(u);
		fa[u]=v;
	}
	void erase(int u,int v){
		makert(u);
		access(v);
		splay(v);
		son[v][0]=0;
		fa[u]=0;
	}
	int getsum(int u,int v){
		makert(u);
		access(v);
		splay(v);
		return sum[v];
	}
	int getlen(int u,int v){
		makert(u);
		access(v);
		splay(v);
		return len[v];
	}
	void plus(int x,int v){
		splay(x);
		val[x]+=v,sum[x]+=v;
	}
}
int n;
namespace seg{
	int t[N*4],tag[N*4];
	void pushdown(int o){
		if(tag[o]){
			t[o<<1]+=tag[o],tag[o<<1]+=tag[o];
			t[o<<1|1]+=tag[o],tag[o<<1|1]+=tag[o];
			tag[o]=0;
		}
	}
	void pushup(int o){
		t[o]=t[o<<1]+t[o<<1|1];
	}
	void add(int L,int R,int v,int l=1,int r=n,int o=1){
		if(L>R) return;
		if(L<=l&&r<=R){
			t[o]+=v;
			tag[o]+=v;
			return;
		}
		int mid=l+r>>1;
		if(L<=mid) add(L,R,v,l,mid,o<<1);
		if(mid<R) add(L,R,v,mid+1,r,o<<1|1);
		pushup(o);
	}
	ll getsum(int L,int R,int l=1,int r=n,int o=1){
		if(L<=l&&r<=R) return t[o];
		int mid=l+r>>1;pushdown(o);ll ret=0;
		if(L<=mid) ret+=getsum(L,R,l,mid,o<<1);
		if(mid<R) ret+=getsum(L,R,mid+1,r,o<<1|1);
		return ret;
	}
}
struct{int u,v;}e[N];
int r1[N],r2[N],r3[N];
int deg[N];
std::vector<std::pair<int,int> > ques[N];
ll ans[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&e[i].u,&e[i].v);
	int q;scanf("%d",&q);
	for(int i=1,l,r;i<=q;i++) scanf("%d%d",&l,&r),ques[l].emplace_back(r,i);
	int r1=n,r2=n,r3=n;
	int cnt2=0;//deg=2
	int cntd=0;//cnt dot
	auto add2=[&cnt2](int u,int v){cnt2+=v;lct::plus(u,v);};
	auto addd=[&cntd](int v){cntd+=v;};
	for(int i=n;i>=1;i--){
		if(lct::conn(e[i].u,e[i].v)){
			r2=r1;
			while(lct::conn(e[i].u,e[i].v)) lct::erase(e[r1].u,e[r1].v),r1--;
		}
		lct::add(e[i].u,e[i].v);
		++deg[e[i].u],++deg[e[i].v];
		if(deg[e[i].u]==1) addd(1);
		if(deg[e[i].v]==1) addd(1);
		if(deg[e[i].u]==2) add2(e[i].u,1);
		if(deg[e[i].v]==2) add2(e[i].v,1);
		if(deg[e[i].u]==3) add2(e[i].u,-1);
		if(deg[e[i].v]==3) add2(e[i].v,-1);
		if(r1<n){
			while(cnt2-lct::getsum(e[r1+1].u,e[r1+1].v)!=lct::getlen(e[r1+1].u,e[r1+1].v)){
				if(deg[e[r3].u]==1) addd(-1);
				if(deg[e[r3].v]==1) addd(-1);
				if(deg[e[r3].u]==2) add2(e[r3].u,-1);
				if(deg[e[r3].v]==2) add2(e[r3].v,-1);
				if(deg[e[r3].u]==3) add2(e[r3].u,1);
				if(deg[e[r3].v]==3) add2(e[r3].v,1);
				--deg[e[r3].u],--deg[e[r3].v];
				r3--;
			}
			r3=std::min(r3,i+cntd-1);
		}
		printf("%d: %d %d %d\n",i,r1,r2,r3);
		seg::add(r1+1,std::min(r2,r3),1);
		for(auto p:ques[i]) ans[p.second]=seg::getsum(i,p.first);
	}
	for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
}
