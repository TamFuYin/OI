#include<bits/stdc++.h>
const int N=1e5;
int a[N],n,d;
int l[N],r[N],g[N];
namespace INIT{
	std::pair<int,int> aa[N];
	int lsh[N],t[N*4];
	void clear(int l=1,int r=n,int o=1){
		t[o]=0;
		if(l==r) return;
		int mid=l+r>>1;
		clear(l,mid,o<<1);
		clear(mid+1,r,o<<1|1);
	}
	int getmax(int L,int R,int l=1,int r=n,int o=1){
		if(L<=l&&r<=R) return t[o];
		int mid=l+r>>1;
		if(L<=mid&&mid<R) return std::max(getmax(L,R,l,mid,o<<1),getmax(L,R,mid+1,r,o<<1|1));
		if(L<=mid) return getmax(L,R,l,mid,o<<1);
		if(mid<R) return getmax(L,R,mid+1,r,o<<1|1);
		exit(-1);
	}
	void insert(int p,int v,int l=1,int r=n,int o=1){
		t[o]=v;
		if(l==r) return;
		int mid=l+r>>1;
		if(p<=mid) insert(p,v,l,mid,o<<1);
		else insert(p,v,mid+1,r,o<<1|1);
	}
	void init(){
		for(int i=1;i<=n;i++) aa[i]=std::make_pair(a[i],i);
		std::sort(aa+1,aa+n+1);
		for(int i=1;i<=n;i++) lsh[i]=std::lower_bound(aa+1,aa+n+1,std::make_pair(a[i],i))-aa;
		clear();
		for(int i=1;i<=n;i++){
			l[i]=getmax(lsh[i],std::upper_bound(aa+1,aa+n+1,std::make_pair(a[i]+d,i))-aa-1);
			g[i]=getmax(lsh[i],n);
			insert(lsh[i],i);
		}
		clear();
		for(int i=n;i>=1;i--){
			r[i]=n+1-getmax(lsh[i],std::upper_bound(aa+1,aa+n+1,std::make_pair(a[i]+d,i))-aa-1);
			insert(lsh[i],n+1-i);
		}
	}
}
std::vector<std::pair<int,int> > Q[N];
std::set<int> S;
std::vector<int> R[N];
int cur[N];
std::stack<int> sta;
struct tag{
	int pl,pc,phm;
	void operator+=(const tag& b){
		if(phm==b.phm+pl) pc+=b.pc;
		else if(b.phm+pl<phm) phm=b.phm+pl,pc=b.pc;
		pl+=b.pl;
	}
}tg[N];
struct data{
	int hm,mc;
	void operator+=(const tag& b){
	}
	data operator+(const data& b)const{
		if(hm==b.hm) return {hm,mc+b.mc};
		else return hm<b.hm?*this:b;
	}
}t[N];
void push(int o,tag v){
	t[o]+=v;tg[o]+=v;
}
void pushup(int o){
	t[o]=t[o<<1]+t[o<<1|1];
}
void add(int L,int R,int v,int l=1,int r=n,int o=1){
	if(L>R) return;
	if(L<=l&&r<=R){
		push(o,{v,1,std::min(0,v)});
		return;
	}
	int mid=l+r>>1;
	if(L<=mid) add(L,R,v,l,mid,o<<1);
	if(mid<R) add(L,R,v,mid+1,r,o<<1|1);
	pushup(o);
}
data query(int L,int R,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) return t[o];
	int mid=l+r>>1;
	if(L<=mid&&mid<R) return query(L,R,l,mid,o<<1)+query(L,R,mid+1,r,o<<1|1);
	if(L<=mid) return query(L,R,l,mid,o<<1);
	if(mid<R) return query(L,R,mid+1,r,o<<1|1);
	exit(-1);
}
int check(data b){
	return b.hm==0?b.mc:0;
}
int ans[N];
int main(){
	int q;scanf("%d%d%d",&n,&d,&q);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	INIT::init();
	for(int i=1;i<=q;i++){
		int l,r;scanf("%d%d",&l,&r);
		Q[r].emplace_back(l,i);
	}
	for(int i=1;i<=n;i++) R[r[i]].push_back(i);
	for(int i=1,j;i<=n;i++){
		add(l[i]+1,cur[i]=g[i],1);
		while(!sta.empty()&&a[j=sta.top()]<=a[i]){
			add(g[j]+1,cur[j]=j,1);
			sta.pop();
		}
		sta.push(i);
		for(int j:R[i]) add(l[j]+1,cur[j],-1);
		for(auto[L,id]:Q[i]) ans[id]=check(query(L,i));
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
}
