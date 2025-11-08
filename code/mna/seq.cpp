#include<bits/stdc++.h>
const int N=5e5+10;
int l[N],r[N],v[N],c[N];
std::vector<int> pl[N],pr[N];
int n;
namespace t1{
	int max[N*4];
	void clear(int l=1,int r=n,int o=1){
		max[o]=0;
		if(l==r) return;
		int mid=l+r>>1;
		clear(l,mid,o<<1);
		clear(mid+1,r,o<<1|1);
	}
	void insert(int p,int v,int l=1,int r=n,int o=1){
		if(l==r){
			max[o]=std::max(max[o],v);
			return;
		}
		int mid=l+r>>1;
		if(p<=mid) insert(p,v,l,mid,o<<1);
		else insert(p,v,mid+1,r,o<<1|1);
		max[o]=std::max(max[o<<1],max[o<<1|1]);
	}
	int askmax(int L,int R,int l=1,int r=n,int o=1){
		if(L<=l&&r<=R) return max[o];
		int mid=l+r>>1,ret=0;
		if(L<=mid) ret=std::max(ret,askmax(L,R,l,mid,o<<1));
		if(mid<R) ret=std::max(ret,askmax(L,R,mid+1,r,o<<1|1));
		return ret;
	}
}
using ll=long long;
const ll INF=1e18;
namespace t2{//动态开点线段树
	ll min[N*10]={INF};
	int size,ls[N*10],rs[N*10];
	ll askmin(int o,int L,int R,int l=1,int r=n){
		if(!o||L>R) return INF;
		if(L<=l&&r<=R) return min[o];
		int mid=l+r>>1;ll ret=INF;
		if(L<=mid) ret=std::min(ret,askmin(ls[o],L,R,l,mid));
		if(mid<R) ret=std::min(ret,askmin(rs[o],L,R,mid+1,r));
		return ret;
	}
	void insert(int& o,int x,ll v,int l=1,int r=n){
		if(!o) o=++size;
		if(l==r){
			min[o]=v;
			return;
		}
		int mid=l+r>>1;
		if(x<=mid) insert(ls[o],x,v,l,mid);
		else insert(rs[o],x,v,mid+1,r);
		min[o]=std::min(min[ls[o]],min[rs[o]]);
	}
	void clear(){
		std::fill(ls+1,ls+size+1,0);
		std::fill(rs+1,rs+size+1,0);
//		std::fill(min,min+size+1,INF);
		size=0;
	}
}
int cc[N];
int rt[N],a[N];
ll f[N];
int b[N];
ll solve(){
	int m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++) pl[i].clear(),pr[i].clear();
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",l+i,r+i,v+i);
		pl[l[i]].push_back(i),pr[r[i]].push_back(i);
	}
	t1::clear();
	for(int i=1;i<=n;i++){
		for(int j:pl[i]) t1::insert(r[j],v[j]);
		c[i]=t1::askmax(i,n);
	}
	std::copy(c+1,c+n+1,cc+1);
	std::sort(cc+1,cc+n+1);
	t2::clear();cc[n+1]=0;
	auto getrk=[](int _c)->int{return std::lower_bound(cc+1,cc+n+1,_c)-cc;};
	for(int i=1;i<=n;i++){
		int rc=getrk(c[i]);
		t2::insert(rt[rc],i,0);
	}
	for(int i=1;i<=m;i++){
		int rv=getrk(v[i]);
		if(cc[rv]!=v[i]||t2::askmin(rt[rv],l[i],r[i])==INF) return -1;
	}
	t2::clear();
	std::fill(b+1,b+n+1,0);
	ll ans=0;
	for(int i=1;i<=n;i++)
		if(a[i]<c[i]) ans+=c[i]-a[i],a[i]=c[i];
	for(int i=1;i<=n;i++){
		if(c[i]){
			int rc=getrk(c[i]);
			f[i]=(b[rc]?t2::askmin(rt[rc],b[rc],i-1):0)+a[i]-c[i];
			if(f[i]>=INF) f[i]=INF;
			else t2::insert(rt[rc],i,f[i]);
		}
		for(int j:pr[i]){
			int rv=getrk(v[j]);
			b[rv]=std::max(b[rv],l[j]);
		}
	}
	for(int i=1;i<=n;i++) if(i==1||cc[i]!=cc[i-1]){
		ll tmp;
		ans+=tmp=t2::askmin(rt[i],b[i],n);
		if(tmp==INF) return -1;
	}
	return ans;
}
int main(){
	freopen("sequence2.in","r",stdin);
	int T;scanf("%d",&T);
	while(T--) printf("%lld\n",solve());
}
