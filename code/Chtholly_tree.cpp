#include<bits/stdc++.h>
const int N=1e5;
int a[N];
struct node{
	int l;
	mutable int r,val;
	bool operator<(const node& a){
		return l<a.l;
	}
	node(int l=0,int r=0,int v=0):l(l),r(r),val(v){}
};
std::set<node> s;
using sit=std::set<node>::iterator;
const int MOD=1e9+7;
sit split(int k){
	sit t=--s.upper_bound(k);
	if(t->l==k) return t;
	int tmp=t->r;t->r=k-1;
	return s.emplace(k,tmp).first;
}
int getsum(int l,int r){
	int ret=0;
	for(sit i=split(l),end=split(r+1);i!=end;i++){
		(ret+=i->val)%=MOD;
	}
	return ret;
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
}
