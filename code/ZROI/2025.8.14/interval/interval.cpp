#include<bits/stdc++.h>
const int N=4e5+10;
std::vector<int> to[N];
int siz[N],son[N],fa[N],dfn[N],rnk[N],dep[N],top[N],bot[N];
const int MOD=998244353;
using ll=long long;
void muleq(int& a,int b){
	a=(ll)a*b%MOD;
}
int qpow(int a,int b){
	int c=1;
	while(b){
		if(b&1) muleq(c,a);
		muleq(a,a),b>>=1;
	}return c;
}
void dfs1(int u){
	siz[u]=1;
	for(int v:to[u]){
		if(v==fa[u]) continue;
		dep[v]=dep[u]+1;
		fa[v]=u,dfs1(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
int f[N],tot,ot[N];
void dfs2(int u){
	rnk[dfn[u]=++dfn[0]]=u;
	if(son[u]) top[son[u]]=top[u],dfs2(son[u]),bot[u]=bot[son[u]];
	else bot[u]=u;
	for(int v:to[u]){
		if(v==fa[u]||v==son[u]) continue;
		top[v]=v;dfs2(v);
	}
}
int al[N],ar[N];
std::vector<int> vl[N],vr[N];
int lsh[N*2],lshtop;
struct node{
	int mul,pls,sum;
	node operator+(const node& b)const{
		return {int((ll)mul*b.mul%MOD),int(((ll)mul*b.pls+pls)%MOD),int(((ll)sum*b.mul%MOD+b.sum)%MOD)};
	}
	int operator*(int b)const{
		return ((ll)b*mul+pls)%MOD;
	}
}t[N*4];bool cmpl[N*4];
int n;
void pushup(int o){
	cmpl[o]=cmpl[o<<1]&cmpl[o<<1|1];
	if(cmpl[o]) t[o]=t[o<<1]+t[o<<1|1];
}
node cursum;
int bnd;
bool full;
void rec_getr(int L,int R,int l=1,int r=n,int o=1){
	if(!full) return;
	if(L<=l&&r<=R&&cmpl[o]){cursum=t[o]+cursum;return;}
	if(l==r){full=0;bnd=r+1;return;}
	int mid=l+r>>1;
	if(mid<R) rec_getr(L,R,mid+1,r,o<<1|1);
	if(L<=mid) rec_getr(L,R,l,mid,o<<1);
}
void getr(int L,int R){
	full=1;cursum={1,0,0};bnd=L;
	if(L<=R) rec_getr(L,R);
}
void rec_getl(int L,int R,int l=1,int r=n,int o=1){
	if(!full) return;
//	printf("> %d~%d\n",l,r);
	if(L<=l&&r<=R&&cmpl[o]){
//		printf(">> %d~%d : %d\n",rnk[l],rnk[r],t[o].pls);
		cursum=cursum+t[o];
		return;
	}
	if(l==r){full=0;bnd=l-1;return;}
	int mid=l+r>>1;
	if(L<=mid) rec_getl(L,R,l,mid,o<<1);
	if(mid<R) rec_getl(L,R,mid+1,r,o<<1|1);
}
void getl(int L,int R){
	full=1;cursum={1,0,0};bnd=R;
	if(L<=R) rec_getl(L,R);
}
void update(int x,int v,int l=1,int r=n,int o=1){
	if(l==r){
//		printf(">> INS %d\n",l);
		cmpl[o]=1;
		t[o].sum=t[o].mul=t[o].pls=v;
		return;
	}
	int mid=l+r>>1;
	if(x<=mid) update(x,v,l,mid,o<<1);
	else update(x,v,mid+1,r,o<<1|1);
	pushup(o);
}
void era(int x,int l=1,int r=n,int o=1){
	if(l==r){
		cmpl[o]=0;
		return;
	}
	int mid=l+r>>1;
	if(x<=mid) era(x,l,mid,o<<1);
	else era(x,mid+1,r,o<<1|1);
	pushup(o);
}
bool in[N];
int getf(int v){
	getl(dfn[v],dfn[bot[v]]);
//	printf("%d~%d : %d\n",v,bot[v],cursum.pls);
	return cursum*0;
}
void change(int u,int nf){
//	printf("%d : %d -> %d\n",u,f[u],nf);
	getr(dfn[top[u]],dfn[u]-1);
	node v=cursum;int l=bnd;
	tot=(tot+(ll)(v.sum+1)*(nf+MOD-f[u]))%MOD;
	int old=f[rnk[l]];f[u]=nf;f[rnk[l]]=v*f[u];
//	printf(">>> %d\n",rnk[l]);
	if(rnk[l]==top[u]&&in[fa[top[u]]]){
		int v=fa[top[u]];
//		printf("v = %d\n",v);
		f[v]=getf(v);nf=f[v];
		int d=(ll)qpow(old+1,MOD-2)*(f[top[u]]+1)%MOD;
		muleq(nf,d);muleq(ot[v],d);
		update(dfn[v],ot[v]);
		change(v,nf);
	}
}
void erase(int u){
//	printf("ERASE %d\n",u);
	in[u]=0;
	for(int v:to[u]){
		if(v==fa[u]||!in[v]) continue;
		f[v]=getf(v);
	}
	era(dfn[u]);
	change(u,0);
}
void insert(int u){
//	printf("INSERT %d\n",u);
	in[u]=1;
	int nf=1;ot[u]=1;
	for(int v:to[u]){
		if(v==fa[u]||!in[v]) continue;
		muleq(nf,f[v]+1);
		if(v!=son[u]) muleq(ot[u],f[v]+1);
	}
	update(dfn[u],ot[u]);
	change(u,nf);
}
int main(){
//	freopen("interval7.in","r",stdin);
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),
		to[u].push_back(v),to[v].push_back(u);
	dfs1(1);top[1]=1;dfs2(1);std::fill(ot+1,ot+n+1,1);
	for(int i=1;i<=n;i++) scanf("%d%d",al+i,ar+i),lsh[lshtop++]=al[i],lsh[lshtop++]=ar[i];
	std::sort(lsh,lsh+lshtop);lshtop=std::unique(lsh,lsh+lshtop)-lsh;
	for(int i=1;i<=n;i++)
		al[i]=std::lower_bound(lsh,lsh+lshtop,al[i])-lsh,
		ar[i]=std::lower_bound(lsh,lsh+lshtop,ar[i])-lsh;
	for(int i=1;i<=n;i++) vl[al[i]].push_back(i);
	int ans=0;
//	for(int i=1;i<=n;i++) printf("%d : [%d,%d]\n",i,al[i],ar[i]);
	for(int x=0;x<lshtop;x++){
		if(x) for(int j:vr[x-1]) erase(j);
		(ans+=MOD-tot)%=MOD;
//		printf("[%d,%d] : %d\n",x-1,x,tot);
		for(int j:vl[x]) insert(j),vr[ar[j]].push_back(j);
		(ans+=tot)%=MOD;
//		printf("[%d] : %d\n",x,tot);
	}
	printf("%d",ans);
}
