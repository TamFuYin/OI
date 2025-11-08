#include<bits/stdc++.h>
using ll=long long;
const int N=5e5+10;
ll t[N];//BIT
int lowbit(int x){
	return x&-x;
}
int n;
void add(int x,ll v){
	if(!x) return;
	while(x<=n){
		t[x]+=v;
		x+=lowbit(x);
	}
}
ll ask(int x){
	ll ret=0;
	while(x){
		ret+=t[x];
		x-=lowbit(x);
	}
	return ret;
}
int l[N],r[N],v[N];
std::vector<std::pair<int,int> > Q[N];
ll ans[N];
void plus(int t,int len){
	add(t,(ll)v[t]*len);
}
void minus(int t,int len){
	add(t,-(ll)v[t]*len);
}
std::map<int,int> ODT;
int m;
#define x first
#define t second
#define NX std::next
#define PR std::prev
#define R(it) (it==--ODT.end()?m:NX(it)->x-1)
void cover(int l,int r,int t){
	auto lt=--ODT.upper_bound(l),rt=--ODT.upper_bound(r);
//	printf("%d %d\n",lt->x,rt->x);
	if(lt==rt){
		minus(lt->t,r-l+1);
		if(!(l==lt->x&&r==R(lt))){
			if(r!=R(lt)) ODT[r+1]=lt->t;
			if(l==lt->x) ODT.erase(lt);
		}
	}
	else{
		auto nlt=NX(lt);
		minus(lt->t,nlt->x-l);
		minus(rt->t,r-rt->x+1);
		if(l==lt->x) ODT.erase(lt);
		for(auto i=nlt;i!=rt;ODT.erase(i++))
			minus(i->t,NX(i)->x-i->x);
		if(r!=R(rt)) ODT[r+1]=rt->t;
		ODT.erase(rt);
	}
	ODT[l]=t;plus(t,r-l+1);
//	printf("ODT: ");
//	for(auto i:ODT) printf("%d ",i.x);
//	puts("");
}
int main(){
//	freopen(".in","r",stdin);
	int q;scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++) scanf("%d%d%d",l+i,r+i,v+i);
	for(int i=1,l,r;i<=q;i++) scanf("%d%d",&l,&r),Q[r].emplace_back(l,i);
	ODT[1]=0;
	for(int i=1;i<=n;i++){
		cover(l[i],r[i],i);
		for(auto p:Q[i])
			ans[p.second]=ask(i)-ask(p.first-1);
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);
}
