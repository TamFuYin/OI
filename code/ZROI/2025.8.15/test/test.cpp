#include<bits/stdc++.h>
#define ckmax(a,b) a=std::max(a,b)
const int N=3e5+10;
int n;
using ll=long long;
struct node{
	ll sum;
	int max,tag,len;
}t[N*4];
int a[N];
void pushup(int o){
	t[o].sum=t[o<<1].sum+t[o<<1|1].sum;
	t[o].max=std::max(t[o<<1].max,t[o<<1|1].max);
}
void build(int l=1,int r=n,int o=1){
	t[o].len=r-l+1;
	if(l==r){
		t[o].sum=t[o].max=a[l];
		return;
	}
	int mid=l+r>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	pushup(o);
}
void rebuild(int L,int R,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) return build(l,r,o);
	int mid=l+r>>1;
	if(L<=mid) rebuild(L,R,l,mid,o<<1);
	if(mid<R) rebuild(L,R,mid+1,r,o<<1|1);
	pushup(o);
//	printf("[%d, %d]: %d\n",l,r,t[o].sum);
}
void push(int o,int tag){
	t[o].max=t[o].tag=tag;
	t[o].sum=(ll)tag*t[o].len;
}
void pushdown(int o){
	if(t[o].tag){
		push(o<<1,t[o].tag);
		push(o<<1|1,t[o].tag);
		t[o].tag=0;
	}
}
void mkcover(int L,int R,int p,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) return push(o,p);
	int mid=l+r>>1;pushdown(o);
	if(L<=mid) mkcover(L,R,p,l,mid,o<<1);
	if(mid<R) mkcover(L,R,p,mid+1,r,o<<1|1);
	pushup(o);
}
ll getsum(int L,int R,int l=1,int r=n,int o=1){
	if(L<=l&&r<=R) return t[o].sum;
	int mid=l+r>>1;ll ret=0;pushdown(o);
	if(L<=mid) ret+=getsum(L,R,l,mid,o<<1);
	if(mid<R) ret+=getsum(L,R,mid+1,r,o<<1|1);
	return ret;
}
void preck(int L,int R,int& p,int l=1,int r=n,int o=1){
	if(l==r){
		ckmax(p,t[o].max);
		t[o].sum=t[o].max=p;
		return;
	}
	int mid=l+r>>1;pushdown(o);
	if(L<=l&&r<=R){
		if(t[o<<1].max<=p) push(o<<1,p),preck(L,R,p,mid+1,r,o<<1|1);
		else preck(L,R,p,l,mid,o<<1),p=t[o<<1|1].max;
	}
	if(L<=mid) preck(L,R,p,l,mid,o<<1);
	if(mid<R) preck(L,R,p,mid+1,r,o<<1|1);
	pushup(o);
}
void posck(int L,int R,int& p,int l=1,int r=n,int o=1){
	if(l==r){
		ckmax(p,t[o].max);
		t[o].sum=t[o].max=p;
		return;
	}
	int mid=l+r>>1;pushdown(o);
	if(L<=l&&r<=R){
		if(t[o<<1|1].max<=p) push(o<<1|1,p),posck(L,R,p,l,mid,o<<1);
		else preck(L,R,p,mid+1,r,o<<1|1),p=t[o<<1].max;
	}
	if(mid<R) posck(L,R,p,mid+1,r,o<<1|1);
	if(L<=mid) posck(L,R,p,l,mid,o<<1);
	pushup(o);
}
void print(int l=1,int r=n,int o=1){
	if(l==r){
		printf("%d ",t[o].max);
		return;
	}
	int mid=l+r>>1;
	pushdown(o);
	print(l,mid,o<<1);
	print(mid+1,r,o<<1|1);
}
std::map<int,int> ODT;
#define fir first
#define sec second
void bfpreck(int l,int r,int& p){
	for(int i=l;i<=r;i++) ckmax(p,a[i]),a[i]=p;
	rebuild(l,r);
}
void bfposck(int l,int r,int& p){
	for(int i=r;i>=l;i--) ckmax(p,a[i]),a[i]=p;
	rebuild(l,r);
}
void solve(int op,int l,int r){
	auto L=--ODT.upper_bound(l),R=ODT.upper_bound(r);
	if(R->fir-1>r) R=ODT.emplace(r+1,(--R)->sec).fir;
	if(L->fir<l) L=ODT.emplace(l,L->sec).fir;
	int p=0;
	if(op==1){
		for(auto i=L;i!=R;i++){
			int l=i->fir,r=std::next(i)->fir-1;
//			printf("[%d,%d]\n",l,r);
			if(i->sec==0) bfpreck(l,r,p);
			else if(i->sec==1) preck(l,r,p);
			else mkcover(l,r,a[r]=ckmax(p,a[l]));
		}
	}
	else{
		for(auto i=std::prev(R);;i--){
			int l=i->fir,r=std::next(i)->fir-1;
//			printf("[%d,%d]\n",l,r);
			if(i->sec==0) bfposck(l,r,p);
			else if(i->sec==2) posck(l,r,p);
			else mkcover(l,r,a[l]=ckmax(p,a[r]));
			if(i==L) break;
		}
	}
	ODT.erase(L,R);
	ODT.emplace(l,op);
//	print();puts("");
}
int main(){
	freopen("ex_test2.in","r",stdin);
	freopen("test.out","w",stdout);
	int m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	ODT.emplace(1,0);
	ODT.emplace(n+1,114514);
	build();
	for(int i=1,op,l,r;i<=m;i++){
		scanf("%d%d%d",&op,&l,&r);
		if(op==3) printf("%lld\n",getsum(l,r));
		else solve(op,l,r);
	}
}
