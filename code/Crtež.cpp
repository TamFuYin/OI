#include<bits/stdc++.h>
const int N=1e7;
using ll=long long;
int ls[N],rs[N],size;
ll cntz[N];bool fk[N];
ll n;
void modify(ll L,ll R,int p=1,ll l=1,ll r=n){
	if(L<=l&&r<=R){
		if(fk[p])
		return;
	}
}
int main(){
	int q;scanf("%lld%d",&n,&q);
	cntz[size=1]=n;
	while(q--){
		ll l,r;scanf("%lld%lld",&l,&r);
		modify(l,r);
	}
}